/**
 * @file    device.c
 * @brief   L2: 全局设备表实现
 *
 * 静态数组实现，无动态分配，适合嵌入式。
 * MAX_DEVICES 可根据需要调整。
 */

#include "device.h"

#include <string.h>

#define MAX_DEVICES 16

static device_t g_devices[MAX_DEVICES];
static int g_device_count = 0;

int device_register(const char *name, device_type_t type,
                    const dev_bind_t *bind)
{
    if (!name || g_device_count >= MAX_DEVICES)
        return -1;

    for (int i = 0; i < g_device_count; i++) {
        if (strcmp(g_devices[i].name, name) == 0)
            return -1; /* 重名 */
    }

    g_devices[g_device_count].name = name;
    g_devices[g_device_count].type = type;
    g_devices[g_device_count].bind = *bind;
    g_devices[g_device_count].drv_instance = NULL;
    g_device_count++;

    return 0;
}

device_t *device_find(const char *name)
{
    if (!name)
        return NULL;
    for (int i = 0; i < g_device_count; i++) {
        if (strcmp(g_devices[i].name, name) == 0)
            return &g_devices[i];
    }
    return NULL;
}

int device_count(void)
{
    return g_device_count;
}
