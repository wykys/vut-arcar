#include "i2c.h"

#define TW_START        0x08
#define TW_REP_START    0x10
#define TW_MT_SLA_ACK   0x18
#define TW_MR_SLA_ACK   0x40
#define TW_MT_DATA_ACK  0x28
#define TW_MT_DATA_NACK 0x30
#define TW_MR_DATA_ACK  0x50
#define TW_MR_DATA_NACK 0x58

#define TW_REG_DATA               TWDR0
#define TW_REG_STATUS             TWSR0
#define TW_REG_CONTORL            TWCR0
#define TW_REG_BIT_RATE           TWBR0
#define TW_REG_SLAVE_ADDRESS      TWAR0
#define TW_REG_SLAVE_ADDRESS_MASK TWAMR0

#define TW_SEND_START     TW_REG_CONTORL = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN)
#define TW_SEND_STOP      TW_REG_CONTORL = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN)
#define TW_SEND_DATA      TW_REG_CONTORL = (1<<TWINT) | (1<<TWEN)
#define TW_READ_DATA_ACK  TW_REG_CONTORL = (1<<TWINT) | (1<<TWEN) | (1<<TWEA)
#define TW_READ_DATA_NACK TW_REG_CONTORL = (1<<TWINT) | (1<<TWEN)
#define TW_STATUS_MASK    0b11111000
#define TW_STATUS         (TW_REG_STATUS & TW_STATUS_MASK)
#define TW_WAIT           while(!(TW_REG_CONTORL & (1<<TWINT)))

void i2c_init(void)
{
    TW_REG_STATUS = 0;
    TW_REG_BIT_RATE = ((F_CPU / F_I2C) - 16) / 2; // must be > 10 for stable operation
    TW_REG_CONTORL = (1<<TWEN);                   // TWI on
}

void i2c_stop(void)
{
    TW_SEND_STOP;
}

state_t i2c_send_address(uint8_t addr, i2c_mode_t mode)
{
    addr = (addr << 1) | mode;

    TW_SEND_START;
    TW_WAIT;

    if ( (mode == I2C_WRITE && TW_STATUS != TW_START) || \
         (mode == I2C_READ  && TW_STATUS != TW_REP_START) )
    {
        #ifdef DEBUG
            usb_puts("ERR: send start\n");
        #endif
        return ERROR;
    }

    TW_REG_DATA = addr;
    TW_SEND_DATA;
    TW_WAIT;

    if ( (mode == I2C_WRITE && TW_STATUS != TW_MT_SLA_ACK) || \
         (mode == I2C_READ  && TW_STATUS != TW_MR_SLA_ACK) )
    {
        TW_SEND_STOP;
        #ifdef DEBUG
            usb_puts("ERR: send address\n");
        #endif
        return ERROR;
    }

    return SUCCES;
}

state_t i2c_send_byte(uint8_t data)
{
    TW_REG_DATA = data;
    TW_SEND_DATA;
    TW_WAIT;
    if (TW_STATUS != TW_MT_DATA_ACK)
    {
        TW_SEND_STOP;
        #ifdef DEBUG
            usb_puts("ERR: data ack\n");
        #endif
        return ERROR;
    }
    return SUCCES;
}

state_t i2c_receive_byte_ack(uint8_t *data)
{
    TW_READ_DATA_ACK;
    TW_WAIT;
    if (TW_STATUS != TW_MR_DATA_ACK)
    {
        #ifdef DEBUG
            usb_puts("ERR: read status not ACK");
        #endif
        return ERROR;
    }

    *data = TW_REG_DATA;
    return SUCCES;
}

state_t i2c_receive_byte_nack(uint8_t *data)
{
    TW_READ_DATA_NACK;
    TW_WAIT;
    if (TW_STATUS != TW_MR_DATA_NACK)
    {
        #ifdef DEBUG
            usb_puts("ERR: read status not NACK");
        #endif
        return ERROR;
    }

    *data = TW_REG_DATA;
    return SUCCES;
}

state_t i2c_write(uint8_t addr_dev, uint8_t addr_reg, uint8_t *data, uint8_t size)
{
    uint8_t i;

    if (i2c_send_address(addr_dev, I2C_WRITE) == ERROR)
        return ERROR;

    if (i2c_send_byte(addr_reg) == ERROR)
        return ERROR;

    for (i=0; i < size; i++)
    {
        if (i2c_send_byte(*(data+i)) == ERROR)
            return ERROR;
    }

    TW_SEND_STOP;
    return SUCCES;
}

state_t i2c_read(uint8_t addr_dev, uint8_t addr_reg, uint8_t *data, uint8_t size)
{
    uint8_t i;
    
    if (i2c_send_address(addr_dev, I2C_WRITE) == ERROR)
        return ERROR;

    if (i2c_send_byte(addr_reg) == ERROR)
        return ERROR;

    if (i2c_send_address(addr_dev, I2C_READ) == ERROR)
        return ERROR;

    for (i=0; i+1 < size; i++)
    {
        if (i2c_receive_byte_ack(data+i) == ERROR)
            return ERROR;
    }

    if (i2c_receive_byte_nack(data+i) == ERROR)
        return ERROR;

    TW_SEND_STOP;
    return SUCCES;
}
