#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"

int main() {
  uart_init();

  while(1) {
    int u = uart_tx();

    _delay_ms(2000);
  }
}
