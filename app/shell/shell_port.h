#ifndef __SHELL_PORT_H__
#define __SHELL_PORT_H__

#include "stdinc.h"

/**
 * @brief Initialize the shell module and bind it to the underlying UART.
 */
void shell_init(void);

/**
 * @brief Shell processing task.
 *        Should be called periodically in the main loop or an RTOS task.
 */
void shell_task(void);

#endif // __SHELL_PORT_H__