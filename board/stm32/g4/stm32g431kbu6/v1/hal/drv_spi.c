#include "drv_spi.h"
#include "drv_gpio.h"

static drv_spi_dev_t *g_head = NULL;

static drv_spi_dev_t *instance_get_dev(uint8_t instance)
{
    drv_spi_dev_t *dev;
    for (dev = g_head; dev != NULL; dev = dev->next) {
        if (dev->instance == instance)
            return dev;
    }
    return NULL;
}

void drv_spi_init(drv_spi_dev_t *dev)
{
    if (dev == NULL || dev->hspi == NULL)
        return;

    dev->next = g_head;
    g_head    = dev;
}

int drv_spi_transfer(uint8_t instance, const uint8_t *tx, uint8_t *rx, uint16_t len)
{
    drv_spi_dev_t *dev = instance_get_dev(instance);
    if (dev == NULL || len == 0)
        return -1;

    drv_gpio_write(dev->cs_instance, 0);

    HAL_StatusTypeDef st;
    if (tx && rx)
        st = HAL_SPI_TransmitReceive(dev->hspi, (uint8_t *)tx, rx, len, 1000);
    else if (tx)
        st = HAL_SPI_Transmit(dev->hspi, (uint8_t *)tx, len, 1000);
    else if (rx)
        st = HAL_SPI_Receive(dev->hspi, rx, len, 1000);
    else
        st = HAL_ERROR;

    drv_gpio_write(dev->cs_instance, 1);

    return (st == HAL_OK) ? (int)len : -1;
}
