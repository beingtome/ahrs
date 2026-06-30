#ifndef __DRV_UART_H__
#define __DRV_UART_H__

#include "lwrb.h"
#include "stdinc.h"
#include "stm32g4xx_hal.h"

#define DRV_UART_MODE_DMA 0
#define DRV_UART_MODE_IT  1

typedef void (*drv_uart_rx_cb_t)(uint8_t instance, uint16_t len);

typedef struct drv_uart_dev {
    UART_HandleTypeDef *huart;
    uint8_t instance;
    uint8_t mode;
    uint8_t *rx_buf;
    uint16_t rx_len;
    uint8_t *rb_buf;
    uint16_t rb_size;
    lwrb_t rb;
    drv_uart_rx_cb_t rx_cb;
    struct drv_uart_dev *next;
} drv_uart_dev_t;

void drv_uart_init(drv_uart_dev_t *dev);
int drv_uart_write(uint8_t instance, const uint8_t *data, uint16_t len);
int drv_uart_read(uint8_t instance, uint8_t *buf, uint16_t len);
void drv_uart_flush(uint8_t instance);

#endif /* __DRV_UART_H__ */
