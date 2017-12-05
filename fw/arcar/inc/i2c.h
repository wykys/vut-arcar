/*
·* library for work with I2C
·*
·* autor: wykys
·* verze: 1.0
·* datum: 2.11.2017
·*/

#ifndef WYK_I2C_H_INCLUDED
#define WYK_I2C_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include "settings.h"
#include "state.h"
#include "usb.h"
#include <avr/io.h>

#define F_I2C 100000UL // Hz

typedef enum {
    I2C_WRITE,
    I2C_READ
} i2c_mode_t;

// ========================================================
void i2c_init(void);
state_t i2c_send_address(uint8_t addr, i2c_mode_t mode);
void i2c_stop(void);
state_t i2c_send_byte(uint8_t data);
state_t i2c_receive_byte_ack(uint8_t *data);
state_t i2c_receive_byte_nack(uint8_t *data);
// --------------------------------------------------------
state_t i2c_write(uint8_t addr_dev, uint8_t addr_reg, uint8_t *data, uint8_t size);
state_t i2c_read(uint8_t addr_dev, uint8_t addr_reg, uint8_t *data, uint8_t size);
// ========================================================

#ifdef __cplusplus
}
#endif // END C++
#endif // WYK_I2C_H_INCLUDED
