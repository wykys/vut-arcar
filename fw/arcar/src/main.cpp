#include "settings.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#ifdef __cplusplus
}
#endif

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
    led_init();
    usb_init();
    bluetooth_init();
    i2c_init();
    motor_init();
    _delay_ms(100);
    sei();

    LSM9DS1 imu(LSM9DS1_AG_ADDR(1), LSM9DS1_M_ADDR(1));

    if (!imu.begin())
    {
        usb_puts((char*)"Failed to communicate with LSM9DS1.\n");
        while(1);
    }

    imu.calibrate();

    while (1)
    {
        imu.readTemp();
        imu.readMag();
        imu.readGyro();
        imu.readAccel();

        printf("gyro [deg/s]: %3.3f %3.3f %3.3f  ||  ", imu.calcGyro(imu.gx), imu.calcGyro(imu.gy), imu.calcGyro(imu.gz));
        printf("accel [g]: %3.3f %3.3f %3.3f  ||  ", imu.calcAccel(imu.ax), imu.calcAccel(imu.ay), imu.calcAccel(imu.az));
        printf("mag [gauss]: %3.3f %3.3f %3.3f  ||  ", imu.calcMag(imu.mx), imu.calcMag(imu.my), imu.calcMag(imu.mz));
        printf("temp [degC]: %4.3f\n", 25.0  + ((double)imu.temperature) / 16.0);

        _delay_ms(50);
    }
}
