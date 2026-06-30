/**
 * @file    printf_port.c
 * @brief   Printf library porting layer - redirects output to UART
 * @note    This file implements _putchar() required by printf library
 */

#include "board_config.h"
#include "drv_board.h"
#include "printf.h"

/**
 * @brief  Low-level character output for printf library
 * @param  character  Character to output
 * @note   Called internally by printf_(), sprintf_(), etc.
 */
void _putchar(char character)
{
    drv_uart_write(UART_INSTANCE, (uint8_t *)&character, 1);
}
