#ifndef UART_H
#define UART_H

void serial_init(unsigned short);
void serial_bufferout(uint8_t *);
void serial_tx(uint8_t);

#define FOSC 7372800           // Clock frequency
#define BAUD 115200               // Baud rate used
#define MYUBRR (FOSC/16/BAUD-1) // Value for UBRR0 register

#endif // UART_H
