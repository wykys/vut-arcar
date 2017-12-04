/*
 * library for work with LED
 *
 * autor: wykys
 * verze: 1.0
 * datum: 2.11.2017
 */

#ifndef WYK_LED_H_INCLUDED
#define WYK_LED_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include "settings.h"
#include <avr/io.h>

#define LED_FRONT_LEFT_PIN   (1<<PC0)
#define LED_FRONT_RIGHT_PIN  (1<<PC1)
#define LED_BACK_LEFT_PIN    (1<<PC2)
#define LED_BACK_RIGHT_PIN   (1<<PC3)

#define LED_DDR   DDRC
#define LED_PIN   PINC
#define LED_PORT  PORTC

#define fl_led_on() (LED_PORT |= LED_FRONT_LEFT_PIN)
#define fl_led_off() (LED_PORT &= ~LED_FRONT_LEFT_PIN)
#define fr_led_on() (LED_PORT |= LED_FRONT_RIGHT_PIN)
#define fr_led_off() (LED_PORT &= ~LED_FRONT_RIGHT_PIN)
#define bl_led_on() (LED_PORT |= LED_BACK_LEFT_PIN)
#define bl_led_off() (LED_PORT &= ~LED_BACK_LEFT_PIN)
#define br_led_on() (LED_PORT |= LED_BACK_RIGHT_PIN)
#define br_led_off() (LED_PORT &= ~LED_BACK_RIGHT_PIN)

// ========================================================
void led_init(void);
// ========================================================

#ifdef __cplusplus
}
#endif // END C++
#endif // WYK_LED_H_INCLUDED
