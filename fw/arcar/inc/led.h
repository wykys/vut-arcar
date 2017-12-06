/*
·* LED driver
·*
·* autor: wykys
·* verze: 1.0
·* datum: 2.11.2017
·*/

#ifndef WYK_LED_H_INCLUDED
#define WYK_LED_H_INCLUDED

#include "settings.h"
#include <avr/io.h>

#define LED_FRONT_LEFT_PIN   (1<<PC0)
#define LED_FRONT_RIGHT_PIN  (1<<PC1)
#define LED_BACK_LEFT_PIN    (1<<PC2)
#define LED_BACK_RIGHT_PIN   (1<<PC3)

#define LED_DDR   DDRC
#define LED_PIN   PINC
#define LED_PORT  PORTC

#define LED_ON  true
#define LED_OFF false

// ========================================================
class LED
{
public:
    LED();
    void forward_left(bool state);
    void forward_right(bool state);
    void reverse_left(bool state);
    void reverse_right(bool state);
};
// ========================================================

#endif // WYK_LED_H_INCLUDED
