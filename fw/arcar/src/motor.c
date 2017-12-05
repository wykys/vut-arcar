#include "motor.h"
#include <util/delay.h>

#define MOTOR_TIMER_TOP 255

void motor_init(void)
{
    MOTOR_DDR |= MOTOR_PWM_PIN | MOTOR_DIR_PIN;
    MOTOR_PORT |= MOTOR_DIR_PIN;
    // Phase Correct and Frequency Correct PWM MODE 1
    OCR1A = MOTOR_TIMER_TOP;
    OCR1B = 0;
    TCCR1A = (1<<WGM10) | (1<<COM1B1);
    TCCR1B = (1<<WGM13) | (1<<CS11); // F_CPU / 8
}

void motor_power(uint8_t power, uint8_t direction)
{
    if (direction == MOTOR_DIRECTION_FORWARD)
    {
        OCR1B = power;
        MOTOR_PORT |= MOTOR_DIR_PIN;
    }
    else
    {
        OCR1B = MOTOR_TIMER_TOP - power;
        MOTOR_PORT &= ~MOTOR_DIR_PIN;
    }
}

void motor_forward(uint8_t power)
{
    OCR1B = MOTOR_TIMER_TOP - power;
    MOTOR_PORT |= MOTOR_DIR_PIN;
}

void motor_reverse(uint8_t power)
{
    OCR1B = power;
    MOTOR_PORT &= ~MOTOR_DIR_PIN;
}
