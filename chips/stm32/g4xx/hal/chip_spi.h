/**
 * @file    chip_spi.h
 * @brief   L1: STM32 SPI 总线工厂
 *
 * AT32:  at32_spi_create(spi_handle_type *handle)
 * ESP32: esp32_spi_create(spi_host_device_t host, int mosi, int miso, int sclk)
 */

#ifndef __CHIP_SPI_H
#define __CHIP_SPI_H

#include "bus_spi.h"

#ifdef __cplusplus
extern "C" {
#endif

bus_spi_t *stm32_spi_create(void *hspi);

#ifdef __cplusplus
}
#endif

#endif /* __CHIP_SPI_H */
