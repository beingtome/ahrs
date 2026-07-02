#ifndef __DRV_CRC_H__
#define __DRV_CRC_H__

#include "stdinc.h"

uint32_t drv_crc32(const uint8_t *data, uint32_t len);
uint16_t drv_crc16_modbus(const uint8_t *data, uint32_t len);

#endif /* __DRV_CRC_H__ */
