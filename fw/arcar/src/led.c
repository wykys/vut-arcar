#include "led.h"

void led_init(void)
{
    LED_DDR |= LED_FRONT_LEFT_PIN | LED_FRONT_RIGHT_PIN | LED_BACK_LEFT_PIN | LED_BACK_RIGHT_PIN;
}
