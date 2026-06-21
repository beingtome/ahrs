/**
 * @file    device.h
 * @brief   L2: 全局设备注册与发现
 *
 * board_init() 将板载设备注册到此表，L5 应用层通过 device_find() 按名称发现。
 * 这是 boards 层与上层之间唯一的运行时数据通道。
 */

#ifndef __DEVICE_H
#define __DEVICE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ---- 设备类型枚举 ---- */
typedef enum {
    DEV_TYPE_UNKNOWN = 0,
    DEV_TYPE_IMU,
    DEV_TYPE_MAG,
    DEV_TYPE_BARO,
    DEV_TYPE_GPS,
    DEV_TYPE_RANGEFINDER,
    DEV_TYPE_OPTICAL_FLOW,
    DEV_TYPE_MAX
} device_type_t;

/* ---- 总线类型枚举 ---- */
typedef enum {
    BUS_TYPE_NONE = 0,
    BUS_TYPE_I2C,
    BUS_TYPE_SPI,
    BUS_TYPE_UART,
} bus_type_t;

/* ---- 设备绑定信息（board 层 → 驱动层）---- */
typedef struct {
    void       *bus;        /* bus_i2c_t* 或 bus_spi_t* */
    uint16_t    addr;       /* I2C 地址（SPI/UART 忽略） */
    void       *cs_pin;     /* SPI 片选 gpio_pin_t*（I2C 忽略） */
} dev_bind_t;

/* ---- 全局设备条目 ---- */
typedef struct {
    const char    *name;         /* "icm42688" — 全局唯一 */
    device_type_t  type;         /* DEV_TYPE_IMU */
    dev_bind_t     bind;         /* 硬件连接信息 */
    void          *drv_instance; /* 驱动实例化后填入（imu_dev_t* 等） */
} device_t;

/* ---- API ---- */

/**
 * @brief  注册一个设备到全局设备表（供 board_init 调用）
 * @return 0 成功, -1 表满
 */
int device_register(const char *name, device_type_t type, const dev_bind_t *bind);

/**
 * @brief  按名称查找设备（供 L5 应用层调用）
 * @return 找到返回 device_t*，未找到返回 NULL
 */
device_t *device_find(const char *name);

/**
 * @brief  遍历所有已注册设备（调试用）
 */
int device_count(void);

#ifdef __cplusplus
}
#endif

#endif /* __DEVICE_H */
