#include "drv_gpio.h"

static drv_gpio_dev_t *g_head = NULL;

static drv_gpio_dev_t *instance_get_dev(uint8_t instance)
{
    drv_gpio_dev_t *dev;
    for (dev = g_head; dev != NULL; dev = dev->next) {
        if (dev->instance == instance) {
            return dev;
        }
    }
    return NULL;
}

void drv_gpio_init(drv_gpio_dev_t *dev)
{
    if (dev == NULL || dev->port == NULL) {
        return;
    }

    dev->next = g_head;
    g_head = dev;
}

void drv_gpio_write(uint8_t instance, uint8_t value)
{
    drv_gpio_dev_t *dev = instance_get_dev(instance);
    if (dev == NULL) {
        return;
    }

    HAL_GPIO_WritePin(dev->port, dev->pin,
                      value ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

uint8_t drv_gpio_read(uint8_t instance)
{
    drv_gpio_dev_t *dev = instance_get_dev(instance);
    if (dev == NULL) {
        return 0;
    }

    return (HAL_GPIO_ReadPin(dev->port, dev->pin) == GPIO_PIN_SET) ? 1 : 0;
}

void drv_gpio_toggle(uint8_t instance)
{
    drv_gpio_dev_t *dev = instance_get_dev(instance);
    if (dev == NULL) {
        return;
    }

    HAL_GPIO_TogglePin(dev->port, dev->pin);
}
