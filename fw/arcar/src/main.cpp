#include "settings.h"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "i2c.h"
#include "led.h"
#include "usb.h"
#include "motor.h"
#include "bluetooth.h"

#include "LSM9DS1.h"
#include "LSM9DS1_registers.h"

#include "wyk_stdio.h"

ISR(BLUETOOTH_RX_vect)
{
    uint8_t tmp = BLUETOOTH_DATA;
    usb_putc(tmp);
}

ISR(USB_RX_vect)
{
    uint8_t tmp = USB_DATA;
    bluetooth_putc(tmp);
}

int main(void)
{
    // bluetooth_servise();
    usb_init();
    bluetooth_init();
    i2c_init();
    _delay_ms(100);
    sei();

    LSM9DS1 imu;
    LED led;
    Motor motor;

    motor.forward(75);

    led.forward_left(true);
    led.forward_right(true);
    led.reverse_left(true);
    led.reverse_right(true);

    if (!imu.begin())
    {
        usb_puts((char *) "Failed to communicate with LSM9DS1.\n");
        while (1)
            ;
    }

    imu.calibrate();

    while (1)
    {
        imu.readTemp();
        imu.readMag();
        imu.readGyro();
        imu.readAccel();

        printf("deg/s: %3.0f %3.0f %3.0f  |  ", imu.calcGyro(imu.gx), imu.calcGyro(imu.gy), imu.calcGyro(imu.gz));
        printf("a [g]: %2.1f %2.1f %2.1f  |  ", imu.calcAccel(imu.ax), imu.calcAccel(imu.ay), imu.calcAccel(imu.az));
        printf("B [uT]: %4.0f %4.0f %4.0f  |  ", imu.calcMag(imu.mx) * 100, imu.calcMag(imu.my) * 100, imu.calcMag(imu.mz) * 100);
        printf("T [C]: %2.1f\n", 25.0 + ((double) imu.temperature) / 16.0);
    }
} // main
