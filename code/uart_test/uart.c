#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "uart.h"

void serial_init(unsigned short ubrr_value)
{

    // Set up USART0 registers
    UBRR0 = ubrr_value;                       // Set baud rate
    UCSR0C = (3 << UCSZ00);               // Async., no parity,
                                          // 1 stop bit, 8 data bits
    UCSR0B |= (1 << TXEN0);  // Enable RX and TX
}

void serial_tx(uint8_t ch)
{
    while ((UCSR0A & (1<<UDRE0)) == 0);
    UDR0 = ch;
}

void serial_stringout(uint8_t *s)
{
    int i = 0;
    while(i < 7) {
        serial_tx(s[i]);
        i++;
    }

}
