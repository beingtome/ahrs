#ifndef __DRV_FLASH_H__
#define __DRV_FLASH_H__

#include "stdinc.h"
#include "stm32g4xx_hal.h"

#define DRV_FLASH_BASE       FLASH_BASE
#define DRV_FLASH_TOTAL_SIZE FLASH_SIZE
#define DRV_FLASH_PAGE_SIZE  FLASH_PAGE_SIZE
#define DRV_FLASH_PAGE_NB    FLASH_PAGE_NB
#define DRV_FLASH_END        (FLASH_BASE + FLASH_SIZE)

int drv_flash_erase(uint32_t addr, uint32_t len);
int drv_flash_write(uint32_t addr, const uint8_t *data, uint32_t len);
int drv_flash_read(uint32_t addr, uint8_t *data, uint32_t len);

#endif /* __DRV_FLASH_H__ */
