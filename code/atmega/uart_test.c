#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"

int main() {
  serial_init(MYUBRR);

  uint8_t output[7] = {1, 2, 3, 4, 5, 6, 0};

  while(1) {
    serial_bufferout(output);

    _delay_ms(1000);
  }
}
