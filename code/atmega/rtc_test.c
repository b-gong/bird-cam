#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "i2c.h"

int main() {
  DDRC |= 1 << DDC0;

  // RTC init
  rtc_init2();
  // 12:00:00 Monday April 22 2024
  rtc_time rtc = { .sec = 50, .min = 59, .hour = 6, .weekDay = 2, .day = 22, .month = 4, .year = 24 };
  rtc_setTime(&rtc);


  while(1) {
    rtc_gettime(&rtc);

    if(rtc.hour == 7) {
      PORTC |= 1 << PC0;      // Set PC0 to a 1
      _delay_ms(500);
      PORTC &= ~(1 << PC0);   // Set PC0 to a 0
      _delay_ms(500);
    }
    _delay_ms(5);
  }
  return 0;
}
