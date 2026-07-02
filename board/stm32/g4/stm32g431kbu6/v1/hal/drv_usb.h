#ifndef __DRV_USB_H__
#define __DRV_USB_H__

#include "stdinc.h"
#include "lwrb.h"

typedef struct drv_usb_dev {
    uint32_t  instance;
    uint8_t  *rb_buf;
    uint16_t  rb_size;
    lwrb_t    rb;
} drv_usb_dev_t;

void drv_usb_init(drv_usb_dev_t *dev);
int  drv_usb_write(const uint8_t *data, uint16_t len);
int  drv_usb_read(uint8_t *buf, uint16_t len);
void drv_usb_rx_notify(const uint8_t *data, uint16_t len);

#endif /* __DRV_USB_H__ */
