#include "drv_flash.h"

#define DWORD_SIZE 8U

static int flash_range_valid(uint32_t addr, uint32_t len)
{
    if (len == 0 || addr + len < addr)
        return 0;
    if (!IS_FLASH_MAIN_MEM_ADDRESS(addr) ||
        !IS_FLASH_MAIN_MEM_ADDRESS(addr + len - 1))
        return 0;
    return 1;
}

int drv_flash_erase(uint32_t addr, uint32_t len)
{
    if (!flash_range_valid(addr, len))
        return -1;

    uint32_t start_page = (addr - DRV_FLASH_BASE) / DRV_FLASH_PAGE_SIZE;
    uint32_t end_page = (addr + len - 1 - DRV_FLASH_BASE) / DRV_FLASH_PAGE_SIZE;

    FLASH_EraseInitTypeDef erase = {
        .TypeErase = FLASH_TYPEERASE_PAGES,
        .Banks = FLASH_BANK_1,
        .Page = start_page,
        .NbPages = end_page - start_page + 1,
    };

    HAL_FLASH_Unlock();

    uint32_t page_err;
    HAL_StatusTypeDef status = HAL_FLASHEx_Erase(&erase, &page_err);
    __HAL_FLASH_DATA_CACHE_RESET();
    HAL_FLASH_Lock();

    return (status == HAL_OK) ? 0 : -1;
}

int drv_flash_write(uint32_t addr, const uint8_t *data, uint32_t len)
{
    if (data == NULL || !flash_range_valid(addr, len))
        return -1;

    HAL_FLASH_Unlock();

    /*
     * STM32G4 flash must be written in 64-bit double-words.
     * Step 1: if addr is not 64-bit aligned, read-back the full
     *         aligned double-word, patch in the bytes we need,
     *         and write it back.
     */
    uint32_t misalign = addr % DWORD_SIZE;
    if (misalign != 0) {
        uint32_t aligned_addr = addr - misalign;
        uint32_t bytes_to_patch = DWORD_SIZE - misalign;
        if (bytes_to_patch > len)
            bytes_to_patch = len;

        uint64_t word;
        memcpy(&word, (const void *)aligned_addr, sizeof(word));
        memcpy((uint8_t *)&word + misalign, data, bytes_to_patch);

        if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, aligned_addr,
                              word) != HAL_OK)
            goto fail;

        addr += bytes_to_patch;
        data += bytes_to_patch;
        len -= bytes_to_patch;
    }

    /*
     * Step 2: write full aligned double-words.
     */
    while (len >= DWORD_SIZE) {
        uint64_t word;
        memcpy(&word, data, sizeof(word));

        if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, addr, word) !=
            HAL_OK)
            goto fail;

        addr += DWORD_SIZE;
        data += DWORD_SIZE;
        len -= DWORD_SIZE;
    }

    /*
     * Step 3: any remaining bytes (1~7). Read-back then patch.
     */
    if (len > 0) {
        uint64_t word;
        memcpy(&word, (const void *)addr, sizeof(word));
        memcpy(&word, data, len);

        if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, addr, word) !=
            HAL_OK)
            goto fail;
    }

    __HAL_FLASH_DATA_CACHE_RESET();
    HAL_FLASH_Lock();
    return 0;

fail:
    __HAL_FLASH_DATA_CACHE_RESET();
    HAL_FLASH_Lock();
    return -1;
}

int drv_flash_read(uint32_t addr, uint8_t *data, uint32_t len)
{
    if (data == NULL || !flash_range_valid(addr, len))
        return -1;

    memcpy(data, (const void *)addr, len);
    return 0;
}
