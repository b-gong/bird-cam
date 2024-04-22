#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "i2c.h"
#include "motor.h"

int main() {
  motor_init();

  rtc_init2();
  rtc_setTime(0x19, 0x45, 0x30);

  int degree = 180;
  unsigned char i, j, k;

  while(1) {
    rtc_gettime(&i, &j, &k);

    if (k == 0) //spin every minute
    {
      rotate(degree);
    }
    _delay_ms(5);
  }
  return 0;
}
