#include "shell_port.h"

#include "board_config.h"
#include "drv_uart.h"
#include "shell.h"

/**
 * Encapsulate the shell object internally.
 * Top-level application (e.g., main.c) should not see this structure.
 */
Shell shell;

/* Shell input buffer (used internally by letter-shell for command line editing)
 */
static char shell_buffer[512];

/**
 * @brief Shell write function. Binds to our UART driver.
 */
static signed short shell_uart_write(char *data, unsigned short len)
{
    /* Use UART_ID_1 as the console output */
    return (signed short)drv_uart_write(UART_INSTANCE, (const uint8_t *)data,
                                        len);
}

/**
 * @brief Shell read function.
 *        Called internally by letter-shell's task engine.
 */
static signed short shell_uart_read(char *data, unsigned short len)
{
    /* Read from our UART's software RingBuffer */
    return (signed short)drv_uart_read(UART_INSTANCE, (uint8_t *)data, len);
}

/**
 * @brief Initialize the shell module and bind it to the underlying UART.
 */
void shell_init(void)
{
    /* Bind UART to shell read/write hooks */
    shell.write = shell_uart_write;
    shell.read = shell_uart_read;

    /* Initialize the letter-shell engine */
    shellInit(&shell, shell_buffer, sizeof(shell_buffer));
}

/**
 * @brief Shell processing task.
 *        Should be called periodically in the main loop or an RTOS task.
 */
void shell_task(void)
{
    /*
     * Call the internal letter-shell processing engine.
     * This fully encapsulates the `&shell` object pointer.
     */
    shellTask(&shell);
}