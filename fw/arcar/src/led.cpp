#include "led.h"

LED::LED()
{
    LED_DDR |= LED_FRONT_LEFT_PIN | LED_FRONT_RIGHT_PIN | LED_BACK_LEFT_PIN | LED_BACK_RIGHT_PIN;
}

void LED::forward_left(bool state)
{
    if (state == LED_ON)
        LED_PORT |= LED_FRONT_LEFT_PIN;
    else
        LED_PORT &= ~LED_FRONT_LEFT_PIN;
}

void LED::forward_right(bool state)
{
    if (state == LED_ON)
        LED_PORT |= LED_FRONT_RIGHT_PIN;
    else
        LED_PORT &= ~LED_FRONT_RIGHT_PIN;
}

void LED::reverse_left(bool state)
{
    if (state == LED_ON)
        LED_PORT |= LED_BACK_LEFT_PIN;
    else
        LED_PORT &= ~LED_BACK_LEFT_PIN;
}

void LED::reverse_right(bool state)
{
    if (state == LED_ON)
        LED_PORT |= LED_BACK_RIGHT_PIN;
    else
        LED_PORT &= ~LED_BACK_RIGHT_PIN;
}
