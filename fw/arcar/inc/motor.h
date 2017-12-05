/*
 * library for work with motor
 *
 * autor: wykys
 * verze: 1.0
 * datum: 2.11.2017
 */

#ifndef WYK_MOTOR_H_INCLUDED
#define WYK_MOTOR_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include "settings.h"
#include <avr/io.h>

#define MOTOR_ERR_PIN  (1<<PB0)
#define MOTOR_DIR_PIN  (1<<PB1)
#define MOTOR_PWM_PIN  (1<<PB2)

#define MOTOR_DDR   DDRB
#define MOTOR_PIN   PINB
#define MOTOR_PORT  PORTB

#define MOTOR_DIRECTION_FORWARD 1
#define MOTOR_DIRECTION_REAR 0

// ========================================================
void motor_init(void);
void motor_power(uint8_t power, uint8_t direction);
void motor_forward(uint8_t power);
void motor_reverse(uint8_t power);
// ========================================================

#ifdef __cplusplus
}
#endif // END C++
#endif // WYK_MOTOR_H_INCLUDED
