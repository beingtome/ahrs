#include "board.h"

#include "board_config.h"
#include "drv_board.h"
#include "main.h"
#include "spi.h"
#include "usart.h"

static void gpio_init(void)
{
    static drv_gpio_dev_t led = {
        .instance = GPIO_LED_INSTANCE,
        .port = LED_GPIO_Port,
        .pin = LED_Pin,
    };
    drv_gpio_init(&led);

    static drv_gpio_dev_t spi1_cs = {
        .instance = SPI1_CS_GPIO_INSTANCE,
        .port = IMU_CS_GPIO_Port,
        .pin = IMU_CS_Pin,
    };
    drv_gpio_init(&spi1_cs);

    static drv_gpio_dev_t spi3_cs = {
        .instance = SPI3_CS_GPIO_INSTANCE,
        .port = MAGN_CS_GPIO_Port,
        .pin = MAGN_CS_Pin,
    };
    drv_gpio_init(&spi3_cs);
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

static void spi_init(void)
{
    static drv_spi_dev_t spi1 = {
        .hspi = &hspi1,
        .instance = SPI1_INSTANCE,
        .cs_instance = SPI1_CS_GPIO_INSTANCE,
    };
    drv_spi_init(&spi1);

    static drv_spi_dev_t spi3 = {
        .hspi = &hspi3,
        .instance = SPI3_INSTANCE,
        .cs_instance = SPI3_CS_GPIO_INSTANCE,
    };
    drv_spi_init(&spi3);
}

static void usb_init(void)
{
    static uint8_t rb_buf[1024];

    static drv_usb_dev_t usb = {
        .instance = USB_INSTANCE,
        .rb_buf = rb_buf,
        .rb_size = sizeof(rb_buf),
    };
    drv_usb_init(&usb);
}

void board_init(void)
{
    gpio_init();
    uart_init();
    spi_init();
    usb_init();
}
