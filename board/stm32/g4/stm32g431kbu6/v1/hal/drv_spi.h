#ifndef __DRV_SPI_H__
#define __DRV_SPI_H__

#include "stdinc.h"
#include "stm32g4xx_hal.h"

typedef struct drv_spi_dev {
    SPI_HandleTypeDef  *hspi;
    uint32_t            instance;
    uint32_t            cs_instance;
    struct drv_spi_dev *next;
} drv_spi_dev_t;

void drv_spi_init(drv_spi_dev_t *dev);
int  drv_spi_transfer(uint8_t instance, const uint8_t *tx, uint8_t *rx, uint16_t len);

#endif /* __DRV_SPI_H__ */
