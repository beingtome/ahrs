#include "drv_crc.h"

#include "board_config.h"
#include "crc.h"

#ifdef DRV_CRC_HARDWARE

extern CRC_HandleTypeDef hcrc;

#define CRC_HW_IDLE 0
#define CRC_HW_C32  1
#define CRC_HW_C16  2

static uint8_t g_crc_hw = CRC_HW_IDLE;

uint32_t drv_crc32(const uint8_t *data, uint32_t len)
{
    if (data == NULL || len == 0)
        return 0xFFFFFFFF;

    if (g_crc_hw != CRC_HW_C32) {
        g_crc_hw = CRC_HW_C32;
        HAL_CRCEx_Polynomial_Set(&hcrc, 0x04C11DB7U, CRC_POLYLENGTH_32B);
        __HAL_CRC_INITIALCRCVALUE_CONFIG(&hcrc, 0xFFFFFFFFU);
    }

    return HAL_CRC_Calculate(&hcrc, (const uint32_t *)data, len) ^ 0xFFFFFFFF;
}

uint16_t drv_crc16_modbus(const uint8_t *data, uint32_t len)
{
    if (data == NULL || len == 0)
        return 0xFFFF;

    if (g_crc_hw != CRC_HW_C16) {
        g_crc_hw = CRC_HW_C16;
        HAL_CRCEx_Polynomial_Set(&hcrc, 0x8005U, CRC_POLYLENGTH_16B);
        __HAL_CRC_INITIALCRCVALUE_CONFIG(&hcrc, 0xFFFFU);
    }

    return (uint16_t)HAL_CRC_Calculate(&hcrc, (const uint32_t *)data, len);
}

#else /* software fallback */

uint32_t drv_crc32(const uint8_t *data, uint32_t len)
{
    if (data == NULL || len == 0)
        return 0xFFFFFFFF;

    uint32_t crc = 0xFFFFFFFF;
    for (uint32_t i = 0; i < len; i++) {
        crc ^= data[i];
        for (uint8_t j = 0; j < 8; j++) {
            if (crc & 1)
                crc = (crc >> 1) ^ 0xEDB88320;
            else
                crc >>= 1;
        }
    }
    return crc ^ 0xFFFFFFFF;
}

uint16_t drv_crc16_modbus(const uint8_t *data, uint32_t len)
{
    if (data == NULL || len == 0)
        return 0xFFFF;

    uint16_t crc = 0xFFFF;
    for (uint32_t i = 0; i < len; i++) {
        crc ^= data[i];
        for (uint8_t j = 0; j < 8; j++) {
            if (crc & 1)
                crc = (crc >> 1) ^ 0xA001;
            else
                crc >>= 1;
        }
    }
    return crc;
}

#endif
