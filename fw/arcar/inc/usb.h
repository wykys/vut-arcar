/*
 * library for work with UART
 *
 * autor: wykys
 * verze: 1.0
 * datum: 2.11.2017
 */

#ifndef WYK_USB_H_INCLUDED
#define WYK_USB_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include "settings.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#define USB_RX_vect USART1_RX_vect
#define USB_DATA UDR1

// ========================================================
void usb_init(void);
void usb_putc(const char data);
void usb_puts(const char str[]);
char usb_getc(void);
// ========================================================

#ifdef __cplusplus
}
#endif // END C++
#endif // WYK_USB_H_INCLUDED
