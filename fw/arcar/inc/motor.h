/*
 * library for work with motor
 *
 * autor: wykys
 * verze: 1.0
 * datum: 5.12.2017
 */

#ifndef WYK_MOTOR_H_INCLUDED
#define WYK_MOTOR_H_INCLUDED

#include "settings.h"
#include <avr/io.h>
#include <util/delay.h>

#define MOTOR_ERR_PIN  (1<<PB0)
#define MOTOR_DIR_PIN  (1<<PB1)
#define MOTOR_PWM_PIN  (1<<PB2)

#define MOTOR_DDR   DDRB
#define MOTOR_PIN   PINB
#define MOTOR_PORT  PORTB

#define MOTOR_TIMER_TOP 255

#define MOTOR_DIRECTION_FORVARD true
#define MOTOR_DIRECTION_REVERS  false

// ========================================================
class Motor
{
public:
    Motor(uint8_t power=0, bool directon=MOTOR_DIRECTION_FORVARD);
    void forward(uint8_t power);
    void reverse(uint8_t power);
    void stop();
    void fast_stop();
    uint8_t get_power();
    bool get_directon();
private:
    bool direction;
    uint8_t power;
};
// ========================================================

#endif // WYK_MOTOR_H_INCLUDED
