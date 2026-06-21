/**
 * @file    chip_system.c
 * @brief   STM32G4 系统初始化实现
 *
 * 注意：本文件通过 extern 引用 CubeMX 生成的 main.c 中的函数。
 *       CubeMX main.c 不参与编译，其 HAL 初始化函数由本文件桥接。
 */

#include "chip_system.h"
#include "stm32g4xx_hal.h"

/* CubeMX 生成的函数（在 cubemx Core/Src/main.c 中定义，参与编译但不含 main()） */
extern void SystemClock_Config(void);

int chip_system_init(void)
{
    HAL_Init();
    SystemClock_Config();
    return 0;
}

void chip_system_delay_ms(uint32_t ms)
{
    HAL_Delay(ms);
}

uint32_t chip_system_clock_hz(void)
{
    return HAL_RCC_GetHCLKFreq();
}
