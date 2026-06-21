/**
 * @file    chip_i2c.h
 * @brief   L1: STM32 I2C 总线工厂
 *
 * 创建 bus_i2c_t 实例，将 STM32 HAL 的 I2C_HandleTypeDef 包装为 L2 抽象接口。
 *
 * AT32:  at32_i2c_create(i2c_handle_type *handle)
 * ESP32: esp32_i2c_create(i2c_port_t port, int sda, int scl)
 */

#ifndef __CHIP_I2C_H
#define __CHIP_I2C_H

#include "bus_i2c.h"

#ifdef __cplusplus
extern "C" {
#endif

/* STM32 工厂：传入 CubeMX 生成的 I2C handle，返回 bus_i2c_t* */
bus_i2c_t *stm32_i2c_create(void *hi2c);

#ifdef __cplusplus
}
#endif

#endif /* __CHIP_I2C_H */
