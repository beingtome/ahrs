#include "board.h"

#include "board_config.h"
#include "drv_board.h"
#include "main.h"
#include "usart.h"

static void gpio_init(void)
{
    static drv_gpio_dev_t led = {
        .instance = LED_INSTANCE,
        .port = LED_GPIO_Port,
        .pin = LED_Pin,
        .level = 0,
    };
    drv_gpio_init(&led);
}

static void uart_init(void)
{
    static uint8_t rx_buf[128];
    static uint8_t rb_buf[256];

    static drv_uart_dev_t uart = {
        .huart = &huart2,
        .instance = UART_INSTANCE,
        .mode = DRV_UART_MODE_DMA,
        .rx_buf = rx_buf,
        .rx_len = sizeof(rx_buf),
        .rb_buf = rb_buf,
        .rb_size = sizeof(rb_buf),
    };
    drv_uart_init(&uart);
}

void board_init(void)
{
    gpio_init();
    uart_init();
}
