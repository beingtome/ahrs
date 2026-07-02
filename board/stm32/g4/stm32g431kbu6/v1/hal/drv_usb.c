#include "drv_usb.h"

#include "usb_device.h"
#include "usbd_cdc_if.h"

static drv_usb_dev_t *g_dev = NULL;

void drv_usb_init(drv_usb_dev_t *dev)
{
    if (dev == NULL || dev->rb_buf == NULL)
        return;

    lwrb_init(&dev->rb, dev->rb_buf, dev->rb_size);
    g_dev = dev;
}

int drv_usb_write(const uint8_t *data, uint16_t len)
{
    if (g_dev == NULL || data == NULL || len == 0)
        return -1;

    uint8_t st = USBD_BUSY;
    while (st == USBD_BUSY)
        st = CDC_Transmit_FS((uint8_t *)data, len);

    return (st == USBD_OK) ? (int)len : -1;
}

int drv_usb_read(uint8_t *buf, uint16_t len)
{
    if (g_dev == NULL || buf == NULL || len == 0)
        return -1;

    return (int)lwrb_read(&g_dev->rb, buf, len);
}

void drv_usb_rx_notify(const uint8_t *data, uint16_t len)
{
    if (g_dev == NULL || data == NULL || len == 0)
        return;

    lwrb_write(&g_dev->rb, data, len);
}
