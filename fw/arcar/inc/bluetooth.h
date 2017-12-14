/*
 * library for work with bluetooth
 *
 * autor: wykys
 * verze: 1.0
 * datum: 2.11.2017
 */

#ifndef WYK_BLUETOOTH_H_INCLUDED
#define WYK_BLUETOOTH_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include "settings.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BLUETOOTH_RX_vect USART0_RX_vect
#define BLUETOOTH_DATA UDR0

#define BLT_START_CMD_MODE "$$$"
#define BLT_END_CMD_MODE "---"
#define BLT_SET_SERVISE "SS,C0"
#define BLT_SET_BAUD "SB,05"
#define BLT_GET_BAUD "GB"
#define BLT_ENABLE_UART "SR,0100"
#define BLT_REBOOT "R,1"
#define BLT_SET_NAME "SN,ARCAR-1"
#define BLT_GET_NAME "GN"
#define BLT_ADD_MAC "JB,1,6BAE6A30B594"
#define BLT_SHOW_MAC "JD"
#define BLT_CLEAR_MAC "JC"
#define BLT_HW_INFO "V"
#define BLT_SW_INFO "D"

// ========================================================
void bluetooth_init(void);
void bluetooth_putc(const unsigned char data);
void bluetooth_puts(const char str[]);
void bluetooth_cmd(const char str[]);
void bluetooth_add_mac(const char mac[]);
void bluetooth_servise(void);
#define bluetooth_delay() _delay_ms(10)
// ========================================================

#ifdef __cplusplus
}
#endif // END C++
#endif // WYK_BLUETOOTH_H_INCLUDED
