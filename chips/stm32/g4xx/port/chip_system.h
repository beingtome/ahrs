/**
 * @file    chip_system.h
 * @brief   L1: STM32G4 系统初始化（HAL + 时钟）
 *
 * 封装 CubeMX 生成的 HAL_Init + SystemClock_Config，
 * 为 board_init 提供统一的芯片初始化入口。
 *
 * AT32/ESP32 版本提供同名接口、不同实现。
 */

#ifndef __CHIP_SYSTEM_H
#define __CHIP_SYSTEM_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

int  chip_system_init(void);
void chip_system_delay_ms(uint32_t ms);
uint32_t chip_system_clock_hz(void);

#ifdef __cplusplus
}
#endif

#endif /* __CHIP_SYSTEM_H */
