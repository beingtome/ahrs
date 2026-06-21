/**
 * @file    bus_i2c.h
 * @brief   L2: I2C 总线抽象接口（跨平台多态）
 *
 * 传感器驱动通过 bus_i2c_t 操作 I2C 总线，不感知底层 MCU。
 * boards 层在 board_init() 时调用芯片工厂函数创建实例，注入给驱动。
 */

#ifndef __BUS_I2C_H
#define __BUS_I2C_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ---- I2C 操作虚表 ---- */
typedef struct bus_i2c_ops {
    int (*read_reg)(void *priv, uint16_t dev_addr,
                    uint8_t reg, uint8_t *buf, uint16_t len);
    int (*write_reg)(void *priv, uint16_t dev_addr,
                     uint8_t reg, const uint8_t *buf, uint16_t len);
    int (*read)(void *priv, uint16_t dev_addr,
                uint8_t *buf, uint16_t len);
    int (*write)(void *priv, uint16_t dev_addr,
                 const uint8_t *buf, uint16_t len);
} bus_i2c_ops_t;

/* ---- I2C 总线实例 ---- */
typedef struct {
    const bus_i2c_ops_t *ops;
    void                *priv;       /* 芯片层私有数据, STM32: &hi2c1 */
} bus_i2c_t;

/* ---- 便捷内联，供驱动使用 ---- */
static inline int bus_i2c_read_reg(bus_i2c_t *bus, uint16_t addr,
                                    uint8_t reg, uint8_t *buf, uint16_t len)
{
    return bus->ops->read_reg(bus->priv, addr, reg, buf, len);
}

static inline int bus_i2c_write_reg(bus_i2c_t *bus, uint16_t addr,
                                     uint8_t reg, const uint8_t *buf, uint16_t len)
{
    return bus->ops->write_reg(bus->priv, addr, reg, buf, len);
}

static inline int bus_i2c_read(bus_i2c_t *bus, uint16_t addr,
                                uint8_t *buf, uint16_t len)
{
    return bus->ops->read(bus->priv, addr, buf, len);
}

static inline int bus_i2c_write(bus_i2c_t *bus, uint16_t addr,
                                 const uint8_t *buf, uint16_t len)
{
    return bus->ops->write(bus->priv, addr, buf, len);
}

#ifdef __cplusplus
}
#endif

#endif /* __BUS_I2C_H */
