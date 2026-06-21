/**
 * @file    bus_spi.h
 * @brief   L2: SPI 总线抽象接口（跨平台多态）
 */

#ifndef __BUS_SPI_H
#define __BUS_SPI_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ---- SPI 操作虚表 ---- */
typedef struct bus_spi_ops {
    int (*transfer)(void *priv, const uint8_t *tx, uint8_t *rx, uint16_t len);
    int (*write_reg)(void *priv, uint8_t reg, const uint8_t *tx, uint16_t len);
    int (*read_reg)(void *priv, uint8_t reg, uint8_t *rx, uint16_t len);
    int (*cs_ctl)(void *priv, int level);  /* 1=assert, 0=deassert */
} bus_spi_ops_t;

/* ---- SPI 总线实例 ---- */
typedef struct {
    const bus_spi_ops_t *ops;
    void                *priv;       /* STM32: &hspi1 */
} bus_spi_t;

/* ---- 便捷内联 ---- */
static inline int bus_spi_transfer(bus_spi_t *bus, const uint8_t *tx,
                                    uint8_t *rx, uint16_t len)
{
    return bus->ops->transfer(bus->priv, tx, rx, len);
}

static inline int bus_spi_write_reg(bus_spi_t *bus, uint8_t reg,
                                     const uint8_t *tx, uint16_t len)
{
    return bus->ops->write_reg(bus->priv, reg, tx, len);
}

static inline int bus_spi_read_reg(bus_spi_t *bus, uint8_t reg,
                                    uint8_t *rx, uint16_t len)
{
    return bus->ops->read_reg(bus->priv, reg, rx, len);
}

static inline int bus_spi_cs_assert(bus_spi_t *bus)   { return bus->ops->cs_ctl(bus->priv, 1); }
static inline int bus_spi_cs_deassert(bus_spi_t *bus) { return bus->ops->cs_ctl(bus->priv, 0); }

#ifdef __cplusplus
}
#endif

#endif /* __BUS_SPI_H */
