/*
 * library for standard input output
 *
 * autor: wykys
 * verze: 1.0
 * datum: 4.12.2017
 */

#ifndef WYK_STDIO_H_INCLUDED
#define WYK_STDIO_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>
#include <avr/io.h>
#include "usb.h"

// ========================================================
void printf(char str[], ...);
// ========================================================

#ifdef __cplusplus
}
#endif // END C++
#endif // WYK_STDIO_H_INCLUDED
