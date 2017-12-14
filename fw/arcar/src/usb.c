#include "usb.h"

void usb_init(void)
{
    UBRR1 = 25;                        // 38400 bps
    UCSR1A = 1<<U2X1;                  // double speed mode
    UCSR1B = (1<<RXEN1) | (1<<TXEN1);  // enable receiver and transmitter
    UCSR1C = 3<<UCSZ10;                // 8n1
    UCSR1B |= 1<<RXCIE1;               // receiver interrupt
}

void usb_putc(const char data)
{
    while ( !( UCSR1A & (1<<UDRE1)) ); // Wait for empty transmit buffer
    UDR1 = data;                       // Put data into buffer, sends the data
}

void usb_puts(const char str[])
{
    for (int i=0; str[i]; i++)
        usb_putc(str[i]);
}

char usb_getc(void)
{
    return USB_DATA;
}
