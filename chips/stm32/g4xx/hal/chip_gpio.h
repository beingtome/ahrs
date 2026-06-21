/**
 * @file    chip_gpio.h
 * @brief   L1: STM32 GPIO 操作封装
 *
 * 将 L2 的 gpio_mode_t/gpio_pull_t 枚举翻译为 STM32 HAL 值。
 * AT32/ESP32 版本提供同名接口，内部翻译为各自平台的寄存器操作。
 */

#ifndef __CHIP_GPIO_H
#define __CHIP_GPIO_H

#include <stdint.h>
#include "drv_gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 初始化一批 GPIO（在 board_init 中遍历设备表调用） */
int chip_gpio_init(const gpio_pin_t *pin);

/* 单 pin 读写 */
int chip_gpio_write(const gpio_pin_t *pin, int level);
int chip_gpio_read(const gpio_pin_t *pin);
int chip_gpio_toggle(const gpio_pin_t *pin);

/* 全局 GPIO 时钟使能（在 board_init 早期调用一次） */
int chip_gpio_init_all(void);

#ifdef __cplusplus
}
#endif

#endif /* __CHIP_GPIO_H */
