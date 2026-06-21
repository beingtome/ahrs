/**
 * @file    chip_gpio.c
 * @brief   STM32 GPIO HAL 封装实现
 */

#include "chip_gpio.h"
#include "stm32g4xx_hal.h"

/* gpio_mode_t → STM32 HAL mode */
static uint32_t stm32_mode(gpio_mode_t m)
{
    switch (m) {
    case GPIO_MODE_INPUT:       return GPIO_MODE_INPUT;
    case GPIO_MODE_OUTPUT_PP:   return GPIO_MODE_OUTPUT_PP;
    case GPIO_MODE_OUTPUT_OD:   return GPIO_MODE_OUTPUT_OD;
    case GPIO_MODE_AF_PP:       return GPIO_MODE_AF_PP;
    case GPIO_MODE_AF_OD:       return GPIO_MODE_AF_OD;
    case GPIO_MODE_ANALOG:      return GPIO_MODE_ANALOG;
    case GPIO_MODE_IT_RISING:   return GPIO_MODE_IT_RISING;
    case GPIO_MODE_IT_FALLING:  return GPIO_MODE_IT_FALLING;
    case GPIO_MODE_IT_BOTH:     return GPIO_MODE_IT_RISING_FALLING;
    default:                    return GPIO_MODE_INPUT;
    }
}

/* gpio_pull_t → STM32 HAL pull */
static uint32_t stm32_pull(gpio_pull_t p)
{
    switch (p) {
    case GPIO_PULLUP:   return GPIO_PULLUP;
    case GPIO_PULLDOWN: return GPIO_PULLDOWN;
    default:            return GPIO_NOPULL;
    }
}

int chip_gpio_init(const gpio_pin_t *pin)
{
    if (!pin || !pin->port) return -1;

    GPIO_InitTypeDef cfg = {0};
    cfg.Pin   = pin->pin;
    cfg.Mode  = stm32_mode(pin->mode);
    cfg.Pull  = stm32_pull(pin->pull);

    if (pin->mode == GPIO_MODE_OUTPUT_PP || pin->mode == GPIO_MODE_OUTPUT_OD)
        cfg.Speed = GPIO_SPEED_FREQ_LOW;

    if (pin->mode >= GPIO_MODE_AF_PP && pin->mode <= GPIO_MODE_AF_OD)
        cfg.Alternate = pin->alternate;

    HAL_GPIO_Init((GPIO_TypeDef *)pin->port, &cfg);
    return 0;
}

int chip_gpio_write(const gpio_pin_t *pin, int level)
{
    if (!pin || !pin->port) return -1;
    HAL_GPIO_WritePin((GPIO_TypeDef *)pin->port, pin->pin,
                      level ? GPIO_PIN_SET : GPIO_PIN_RESET);
    return 0;
}

int chip_gpio_read(const gpio_pin_t *pin)
{
    if (!pin || !pin->port) return -1;
    return HAL_GPIO_ReadPin((GPIO_TypeDef *)pin->port, pin->pin) == GPIO_PIN_SET;
}

int chip_gpio_toggle(const gpio_pin_t *pin)
{
    if (!pin || !pin->port) return -1;
    HAL_GPIO_TogglePin((GPIO_TypeDef *)pin->port, pin->pin);
    return 0;
}

int chip_gpio_init_all(void)
{
    /* CubeMX 生成的 MX_GPIO_Init 已经处理时钟和初始配置 */
    extern void MX_GPIO_Init(void);
    MX_GPIO_Init();
    return 0;
}
