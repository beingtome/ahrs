/**
 * @file    chip_i2c.c
 * @brief   STM32 I2C 工厂实现
 */

#include "chip_i2c.h"

#include <stdlib.h>

#include "stm32g4xx_hal.h"

/* ---- 将 HAL 操作包装为 bus_i2c_ops ---- */

static int stm32_i2c_read_reg(void *priv, uint16_t addr, uint8_t reg,
                              uint8_t *buf, uint16_t len)
{
    I2C_HandleTypeDef *hi2c = (I2C_HandleTypeDef *)priv;
    return HAL_I2C_Mem_Read(hi2c, (uint16_t)(addr << 1), reg,
                            I2C_MEMADD_SIZE_8BIT, buf, len, 100);
}

static int stm32_i2c_write_reg(void *priv, uint16_t addr, uint8_t reg,
                               const uint8_t *buf, uint16_t len)
{
    I2C_HandleTypeDef *hi2c = (I2C_HandleTypeDef *)priv;
    return HAL_I2C_Mem_Write(hi2c, (uint16_t)(addr << 1), reg,
                             I2C_MEMADD_SIZE_8BIT, (uint8_t *)buf, len, 100);
}

static int stm32_i2c_read(void *priv, uint16_t addr, uint8_t *buf, uint16_t len)
{
    I2C_HandleTypeDef *hi2c = (I2C_HandleTypeDef *)priv;
    return HAL_I2C_Master_Receive(hi2c, (uint16_t)(addr << 1), buf, len, 100);
}

static int stm32_i2c_write(void *priv, uint16_t addr, const uint8_t *buf,
                           uint16_t len)
{
    I2C_HandleTypeDef *hi2c = (I2C_HandleTypeDef *)priv;
    return HAL_I2C_Master_Transmit(hi2c, (uint16_t)(addr << 1), (uint8_t *)buf,
                                   len, 100);
}

static const bus_i2c_ops_t stm32_i2c_ops = {
    .read_reg = stm32_i2c_read_reg,
    .write_reg = stm32_i2c_write_reg,
    .read = stm32_i2c_read,
    .write = stm32_i2c_write,
};

bus_i2c_t *stm32_i2c_create(void *hi2c)
{
    bus_i2c_t *bus = (bus_i2c_t *)malloc(sizeof(bus_i2c_t));
    if (!bus)
        return NULL;
    bus->ops = &stm32_i2c_ops;
    bus->priv = hi2c;
    return bus;
}
