#include "motor.h"

Motor::Motor(uint8_t power, bool directon)
{
    // pin configuration
    MOTOR_DDR |= MOTOR_PWM_PIN | MOTOR_DIR_PIN;

    // Phase Correct and Frequency Correct PWM MODE 1
    OCR1A = MOTOR_TIMER_TOP;
    OCR1B = this->power;
    TCCR1A = (1<<WGM10) | (1<<COM1B1);
    TCCR1B = (1<<WGM13) | (1<<CS11); // F_CPU / 8

    if (directon == MOTOR_DIRECTION_FORVARD)
        forward(power);
    else
        reverse(power);
}

void Motor::forward(uint8_t power)
{
    OCR1B = MOTOR_TIMER_TOP - power;
    MOTOR_PORT |= MOTOR_DIR_PIN;
    this->power = power;
    this->direction = MOTOR_DIRECTION_FORVARD;
}

void Motor::reverse(uint8_t power)
{
    OCR1B = power;
    MOTOR_PORT &= ~MOTOR_DIR_PIN;
    this->power = power;
    this->direction = MOTOR_DIRECTION_REVERS;
}

void Motor::stop()
{
    OCR1B = 0;
    MOTOR_PORT &= ~MOTOR_DIR_PIN;
    power = 0;
}

void Motor::fast_stop()
{
    if (direction == MOTOR_DIRECTION_FORVARD)
        while (power)
        {
            reverse(power-1);
            _delay_us(500);
        }
    else
        stop();
}

uint8_t Motor::get_power()
{
    return power;
}

bool Motor::get_directon()
{
    return direction;
}
