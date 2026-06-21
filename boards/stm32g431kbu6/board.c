/**
 * @file    board.c
 * @brief   STM32G431KBU6 板级初始化实现
 *
 * 本文件是 boards 层中唯一可以同时 #include board.h 和芯片 HAL 头文件的文件。
 * 职责：
 *   1. 初始化芯片系统（HAL + 时钟）
 *   2. 初始化板级 GPIO
 *   3. 创建总线实例
 *   4. 注册板载设备到全局设备表
 *
 * 本文件决不：
 *   - 调用传感器驱动的 create 函数
 *   - 包含传感器驱动头文件
 *   - 包含任何业务逻辑
 */

#include "board.h"
#include "board_config.h"
#include "chip_system.h"
#include "chip_gpio.h"
#include "chip_i2c.h"
#include "chip_spi.h"
#include "device.h"

/* ---- CubeMX 生成的 HAL 句柄（在 cubemx Core/Src/main.c 中定义）---- */
extern I2C_HandleTypeDef hi2c1;
extern SPI_HandleTypeDef hspi1;

/* ---- 全局总线实例 ---- */
bus_i2c_t *bus_i2c1 = NULL;
bus_spi_t *bus_spi1 = NULL;

/* ---- 板载设备表 ---- */
const board_dev_desc_t board_devices[] = {
    /*
     * 设备列表。当前只配了 LED（不属于传感器设备表）。
     * I2C/SPI 设备待 CubeMX 配置总线后启用。
     *
     * 示例（CubeMX 配好 I2C1 后取消注释）：
     *
     * { "icm42688", DEV_TYPE_IMU, BUS_TYPE_I2C,
     *   .i2c_addr = 0x68,
     *   .int_pin  = ICM42688_INT_PIN,
     *   .drdy_pin = PIN_NONE },
     *
     * { "mmc5603", DEV_TYPE_MAG, BUS_TYPE_I2C,
     *   .i2c_addr = 0x30,
     *   .int_pin  = MMC5603_INT_PIN,
     *   .drdy_pin = PIN_NONE },
     */

    /* 终止标记 */
    { NULL, DEV_TYPE_UNKNOWN, BUS_TYPE_NONE }
};

/* ---- board_init ---- */
int board_init(void)
{
    /* 步骤 1：芯片层基础初始化 */
    chip_system_init();

    /* 步骤 2：板级 GPIO 初始化（LED, 传感器 INT 引脚等） */
    chip_gpio_init_all();

    /* 初始化板载 LED（初始熄灭） */
    chip_gpio_write(&LED0_PIN, 1);   /* 低电平亮 → 写 1 = 灭 */

    /* 遍历设备表，初始化传感器 INT/DRDY 引脚 */
    for (const board_dev_desc_t *d = board_devices; d->name != NULL; d++) {
        if (d->int_pin.port)  chip_gpio_init(&d->int_pin);
        if (d->drdy_pin.port) chip_gpio_init(&d->drdy_pin);
        if (d->spi_cs.port)   chip_gpio_init(&d->spi_cs);
    }

    /* 步骤 3：创建总线实例（CubeMX 配置总线后启用） */
    /*
     * 待 CubeMX 中使能 I2C1/SPI1 外设，并在其 main.c 中生成
     * MX_I2C1_Init() / MX_SPI1_Init() 后取消注释：
     *
     *   MX_I2C1_Init();
     *   bus_i2c1 = stm32_i2c_create(&hi2c1);
     *
     *   MX_SPI1_Init();
     *   bus_spi1 = stm32_spi_create(&hspi1);
     */

    /* 步骤 4：注册板载设备到全局设备表 */
    for (const board_dev_desc_t *d = board_devices; d->name != NULL; d++) {
        dev_bind_t bind = {0};

        /* 根据总线类型填充绑定信息 */
        switch (d->bus_type) {
        case BUS_TYPE_I2C:
            bind.bus  = bus_i2c1;
            bind.addr = d->i2c_addr;
            break;
        case BUS_TYPE_SPI:
            bind.bus   = bus_spi1;
            bind.cs_pin = (void *)&d->spi_cs;
            break;
        default:
            continue;   /* 跳过未配置总线的占位设备 */
        }

        device_register(d->name, d->type, &bind);
    }

    return 0;
}

const board_dev_desc_t *board_get_devices(void)
{
    return board_devices;
}

const char *board_get_name(void)
{
    return BOARD_NAME;
}
