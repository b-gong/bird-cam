#include <avr/io.h>
#include <util/delay.h>
#include "HX711_light.h"

int main(void) {
  DDRC |= (1 << PC0);

  HX711_init();
  int32_t old_data = readData();
  int32_t data = 0;

  while(1) {
    data = readData();
    if(data - old_data > 100000) {
      while(1) {
        PORTC |= (1 << PC0);
        _delay_ms(500);
        PORTC &= ~(1 << PC0);
        _delay_ms(500);
      }
    }
    _delay_ms(100);
  }
}
