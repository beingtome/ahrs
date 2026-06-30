#ifndef __DRV_GPIO_H__
#define __DRV_GPIO_H__

#include "stdinc.h"
#include "stm32g4xx_hal.h"

typedef struct drv_gpio_dev {
    GPIO_TypeDef *port;
    uint32_t pin;
    uint32_t instance;
    uint8_t level;
    struct drv_gpio_dev *next;
} drv_gpio_dev_t;

void drv_gpio_init(drv_gpio_dev_t *dev);
void drv_gpio_write(uint8_t instance, uint8_t value);
uint8_t drv_gpio_read(uint8_t instance);
void drv_gpio_toggle(uint8_t instance);

#endif /* __DRV_GPIO_H__ */
