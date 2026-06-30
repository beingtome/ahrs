#include "drv_uart.h"

static drv_uart_dev_t *g_head = NULL;

static drv_uart_dev_t *instance_get_dev(uint8_t instance)
{
    drv_uart_dev_t *dev;
    for (dev = g_head; dev != NULL; dev = dev->next) {
        if (dev->instance == instance)
            return dev;
    }
    return NULL;
}

static drv_uart_dev_t *dev_find_by_handle(UART_HandleTypeDef *huart)
{
    drv_uart_dev_t *dev;
    for (dev = g_head; dev != NULL; dev = dev->next) {
        if (dev->huart == huart)
            return dev;
    }
    return NULL;
}

void drv_uart_init(drv_uart_dev_t *dev)
{
    if (dev == NULL || dev->huart == NULL)
        return;

    lwrb_init(&dev->rb, dev->rb_buf, dev->rb_size);

    dev->next = g_head;
    g_head = dev;

    if (dev->mode == DRV_UART_MODE_DMA)
        HAL_UARTEx_ReceiveToIdle_DMA(dev->huart, dev->rx_buf, dev->rx_len);
    else
        HAL_UART_Receive_IT(dev->huart, dev->rx_buf, 1);
}

int drv_uart_write(uint8_t instance, const uint8_t *data, uint16_t len)
{
    drv_uart_dev_t *dev = instance_get_dev(instance);
    if (dev == NULL || data == NULL || len == 0)
        return -1;

    HAL_StatusTypeDef st =
        HAL_UART_Transmit(dev->huart, (uint8_t *)data, len, 1000);
    return (st == HAL_OK) ? (int)len : -1;
}

int drv_uart_read(uint8_t instance, uint8_t *buf, uint16_t len)
{
    drv_uart_dev_t *dev = instance_get_dev(instance);
    if (dev == NULL || buf == NULL || len == 0)
        return -1;

    return (int)lwrb_read(&dev->rb, buf, len);
}

void drv_uart_flush(uint8_t instance)
{
    drv_uart_dev_t *dev = instance_get_dev(instance);
    if (dev == NULL)
        return;

    /* 等待 TX 完成 */
    while (dev->huart->gState != HAL_UART_STATE_READY) {
    }

    /* 清空 RX ring buffer */
    lwrb_reset(&dev->rb);
}

/* ---- HAL Callbacks ---- */
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t size)
{
    drv_uart_dev_t *dev = dev_find_by_handle(huart);
    if (dev == NULL || dev->mode != DRV_UART_MODE_DMA)
        return;

    if (size > 0) {
        lwrb_write(&dev->rb, dev->rx_buf, size);
        if (dev->rx_cb)
            dev->rx_cb(dev->instance, size);
    }
    HAL_UARTEx_ReceiveToIdle_DMA(dev->huart, dev->rx_buf, dev->rx_len);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    drv_uart_dev_t *dev = dev_find_by_handle(huart);
    if (dev == NULL || dev->mode != DRV_UART_MODE_IT)
        return;

    lwrb_write(&dev->rb, dev->rx_buf, 1);
    if (dev->rx_cb)
        dev->rx_cb(dev->instance, 1);
    HAL_UART_Receive_IT(dev->huart, dev->rx_buf, 1);
}
