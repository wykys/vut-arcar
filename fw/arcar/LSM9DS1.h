/*
 * library for work with LSM9DS1
 * akcelerometr, giroskop, magnetometr
 *
 * autor: wykys
 * verze: 1.0
 * datum: 2.11.2017
 */

#ifndef WYK_LSM9DS1_H_INCLUDED
#define WYK_LSM9DS1_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include "settings.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#include "LSM9DS1_registers.h"
#include "i2c.h"

#define I2C_DEV_ADDRRESS_AG 0x6B // 107
#define I2C_DEV_ADDRRESS_M  0x1E //  30

// ========================================================
void LSM9DS1_init(void);
uint16_t LSM9DS1_get_temp(void);
// ========================================================

#ifdef __cplusplus
}
#endif // END C++
#endif // WYK_LSM9DS1_H_INCLUDED
