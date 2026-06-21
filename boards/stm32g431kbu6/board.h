/**
 * @file    board.h
 * @brief   STM32G431KBU6 板级拓扑声明
 */

#ifndef __BOARD_H
#define __BOARD_H

#include <stdint.h>

#include "bus_i2c.h"
#include "bus_spi.h"
#include "device.h"
#include "drv_gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ---- 板级标识 ---- */
#define BOARD_NAME "STM32G431KBU6-AHRS"
#define BOARD_MCU  "STM32G431KBU6"

/* ---- 引脚定义 ---- */
/* LED: PA0, 推挽输出, 低电平亮 */
#define LED0_PIN                                                               \
    ((gpio_pin_t){.port = GPIOA,                                               \
                  .pin = GPIO_PIN_0,                                           \
                  .mode = GPIO_MODE_OUTPUT_PP,                                 \
                  .pull = GPIO_NOPULL})

/*
 * 传感器引脚 — 待 CubeMX 配置 I2C/SPI 后填入具体值。
 *
 * 规划（因本板仅 32 脚 UFQFPN32，引脚紧张）：
 *   ICM-42688-P    I2C1 (PB6=SCL, PB7=SDA), INT=PB0
 *   MMC5603        I2C1 (同上 SCL/SDA),    INT=PB1
 *   BMP390         I2C1 (同上),            INT=PB2 (可选, 暂不用)
 *
 * 当前 CubeMX 未配 I2C1，先以注释占位：
 */
#if 0 /* 待 CubeMX I2C1 配置后取消注释 */
#define ICM42688_INT_PIN                                                       \
    ((gpio_pin_t){.port = GPIOB,                                               \
                  .pin = GPIO_PIN_0,                                           \
                  .mode = GPIO_MODE_IT_RISING,                                 \
                  .pull = GPIO_PULLDOWN})
#define MMC5603_INT_PIN                                                        \
    ((gpio_pin_t){.port = GPIOB,                                               \
                  .pin = GPIO_PIN_1,                                           \
                  .mode = GPIO_MODE_IT_RISING,                                 \
                  .pull = GPIO_PULLDOWN})
#endif

/* 哨兵：未使用的引脚 */
#define PIN_NONE GPIO_PIN_NONE

/* ---- 板载设备描述符 ---- */
typedef struct {
    const char *name;
    device_type_t type;
    bus_type_t bus_type;
    uint16_t i2c_addr;   /* 仅 I2C */
    gpio_pin_t spi_cs;   /* 仅 SPI, 不用时填 PIN_NONE */
    gpio_pin_t int_pin;  /* 中断引脚 */
    gpio_pin_t drdy_pin; /* 数据就绪引脚（可选）*/
} board_dev_desc_t;

/* ---- 板载设备表（extern 声明，定义在 board.c）---- */
extern const board_dev_desc_t board_devices[];

/* ---- 对外 API ---- */
int board_init(void);
const board_dev_desc_t *board_get_devices(void);
const char *board_get_name(void);

/* ---- 全局总线实例（供传感器驱动获取）---- */
extern bus_i2c_t *bus_i2c1;
extern bus_spi_t *bus_spi1;

#ifdef __cplusplus
}
#endif

#endif /* __BOARD_H */
