#include "LSM9DS1.h"

void LSM9DS1_init(void)
{
    ;
}

uint16_t LSM9DS1_get_temp(void)
{
    uint8_t tmp[2];
    i2c_read(I2C_DEV_ADDRRESS_AG, OUT_TEMP_L, tmp, 2);
    return (((uint16_t) tmp[1]) << 8) + tmp[0];
}
