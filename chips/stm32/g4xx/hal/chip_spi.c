/**
 * @file    chip_spi.c
 * @brief   STM32 SPI 工厂实现
 */

#include "chip_spi.h"

#include <stdlib.h>

#include "stm32g4xx_hal.h"

static int stm32_spi_transfer(void *priv, const uint8_t *tx, uint8_t *rx,
                              uint16_t len)
{
    SPI_HandleTypeDef *hspi = (SPI_HandleTypeDef *)priv;
    return HAL_SPI_TransmitReceive(hspi, (uint8_t *)tx, rx, len, 100);
}

static int stm32_spi_write_reg(void *priv, uint8_t reg, const uint8_t *tx,
                               uint16_t len)
{
    /* 组合 reg + data 后单次传输（大部分 SPI 传感器是这样工作的） */
    SPI_HandleTypeDef *hspi = (SPI_HandleTypeDef *)priv;
    HAL_SPI_Transmit(hspi, &reg, 1, 100);
    return HAL_SPI_Transmit(hspi, (uint8_t *)tx, len, 100);
}

static int stm32_spi_read_reg(void *priv, uint8_t reg, uint8_t *rx,
                              uint16_t len)
{
    SPI_HandleTypeDef *hspi = (SPI_HandleTypeDef *)priv;
    uint8_t read_cmd = reg | 0x80; /* 典型 SPI 读命令：高位=1 */
    HAL_SPI_Transmit(hspi, &read_cmd, 1, 100);
    return HAL_SPI_Receive(hspi, rx, len, 100);
}

static int stm32_spi_cs_ctl(void *priv, int level)
{
    /* CS 由 board.c 通过 gpio_pin_t 控制，这里保留接口 */
    (void)priv;
    (void)level;
    return 0;
}

static const bus_spi_ops_t stm32_spi_ops = {
    .transfer = stm32_spi_transfer,
    .write_reg = stm32_spi_write_reg,
    .read_reg = stm32_spi_read_reg,
    .cs_ctl = stm32_spi_cs_ctl,
};

bus_spi_t *stm32_spi_create(void *hspi)
{
    bus_spi_t *bus = (bus_spi_t *)malloc(sizeof(bus_spi_t));
    if (!bus)
        return NULL;
    bus->ops = &stm32_spi_ops;
    bus->priv = hspi;
    return bus;
}
