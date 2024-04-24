#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "HX711_light.h"

int main() {
  // indicator led init
  DDRC |= 1 << DDC0;

  // HX711 init
  HX711_init();
  int32_t tare = readData();
  int32_t data = 0;

  // Init delay to make sure everything works right
  _delay_ms(500);

  /* Main loop
    * Weight sensor trigger (less or equal to interrupt?) -> check rtc -> send UART tx
    * rtc reaches scheduled time -> trigger motors
    * rtc reaches night time -> turn on nightlight
    * rtc reaches morning -> turn off nightlight
  */
  int i;
  while(1) {
    // poll load cell
    data = readData();

    // if weight triggered, check rtc and send uart msg
    if(data - tare > 100000) {
      PORTC |= 1 << PC0;      // Set PC0 to a 1
    } else {
      PORTC &= ~(1 << PC0);
    }

    _delay_ms(100);
  }
}
