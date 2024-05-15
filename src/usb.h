#ifndef USB_H
#define USB_H

#include <stdint.h>

int read_usb_sector(uint32_t lba, uint8_t *buffer);

#endif // USB_H
