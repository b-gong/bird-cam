#include <avr/io.h>

void uart_init() {
  // Control and status registers
  // - Receiver enable
  // - 7-bit messages
  UCSRA = 0x00;
  UCSRB = 0x08; // 00001000
  UCSRC = 0x04; // 00000100
  
  // Baud rate = 115200
  UBRRH = 0x00;
  UBRRL = 0x03;
}

int uart_tx(uint8_t msg) {
  if(!(UCSRA & 0x20)) // if data register not ready to receive new data
    return -1;
  UDR = msg;
  return 1;
}
