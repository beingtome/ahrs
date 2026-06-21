/**
 * @file    drv_gpio.h
 * @brief   L2: 跨平台 GPIO pin 抽象类型
 *
 * 所有芯片无关代码通过此类型描述引脚，芯片层负责将其转换为具体寄存器操作。
 */

#ifndef __DRV_GPIO_H
#define __DRV_GPIO_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ---- GPIO 模式（芯片无关枚举）---- */
typedef enum {
    GPIO_MODE_INPUT         = 0,
    GPIO_MODE_OUTPUT_PP     = 1,
    GPIO_MODE_OUTPUT_OD     = 2,
    GPIO_MODE_AF_PP         = 3,
    GPIO_MODE_AF_OD         = 4,
    GPIO_MODE_ANALOG        = 5,
    GPIO_MODE_IT_RISING     = 6,
    GPIO_MODE_IT_FALLING    = 7,
    GPIO_MODE_IT_BOTH       = 8,
} gpio_mode_t;

/* ---- 上下拉（芯片无关枚举）---- */
typedef enum {
    GPIO_NOPULL  = 0,
    GPIO_PULLUP  = 1,
    GPIO_PULLDOWN = 2,
} gpio_pull_t;

/* ---- GPIO pin 描述符（跨平台统一）---- */
typedef struct {
    void       *port;        /* 芯片相关端口指针, STM32: GPIOA, ESP32: GPIO_NUM_0 */
    uint16_t    pin;         /* 引脚号, STM32: GPIO_PIN_0 */
    gpio_mode_t mode;        /* 芯片无关模式 */
    gpio_pull_t pull;        /* 芯片无关上下拉 */
    uint32_t    alternate;   /* 复用功能号, 仅 GPIO_MODE_AF_xx 时使用 */
} gpio_pin_t;

/* 哨兵：表示引脚未使用 */
#define GPIO_PIN_NONE  ((gpio_pin_t){ .port = NULL, .pin = 0 })

#ifdef __cplusplus
}
#endif

#endif /* __DRV_GPIO_H */
