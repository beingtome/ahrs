/**
 * @file    board_config.h
 * @brief   STM32G431KBU6 板级配置参数（时钟 / 电压 / 功能开关）
 *
 * board.h = 硬件拓扑（有什么、接在哪）
 * board_config.h = 配置参数（跑多快、怎么供电）
 */

#ifndef __BOARD_CONFIG_H
#define __BOARD_CONFIG_H

/* ---- 系统时钟 ---- */
#define BOARD_SYS_CLOCK_HZ  144000000UL /* SYSCLK = HSE 8MHz × 36 / 2 */
#define BOARD_HCLK_HZ       144000000UL
#define BOARD_APB1_CLOCK_HZ 144000000UL
#define BOARD_APB2_CLOCK_HZ 144000000UL

/* ---- 总线速率 ---- */
#define BOARD_I2Cx          1
#define BOARD_I2C1_CLOCK_HZ 400000   /* Fast mode */
#define BOARD_SPI1_CLOCK_HZ 10000000 /* 10 MHz */

/* ---- 供电 ---- */
#define BOARD_VDD_MV 3300

/* ---- 调试串口 ---- */
#define BOARD_DEBUG_UART     1 /* USART1, 待 CubeMX 配置后启用 */
#define BOARD_DEBUG_BAUDRATE 115200

/* ---- 功能开关 ---- */
#define BOARD_ENABLE_FPU    1
#define BOARD_ENABLE_ICACHE 1
#define BOARD_ENABLE_DCACHE 1

/* ---- 板载特性 ---- */
#define BOARD_HAS_LED    1
#define BOARD_HAS_BUTTON 0 /* 本板无按键 */
#define BOARD_HAS_IMU    1 /* 待传感器焊接后启用 */
#define BOARD_HAS_MAG    1
#define BOARD_HAS_BARO   0

#endif /* __BOARD_CONFIG_H */
