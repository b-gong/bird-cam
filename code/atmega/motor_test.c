#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "motor.h"

int main()
{
  motor_init();

  while(1) {
    rotate(90);
    _delay_ms(100);
    rotate(-90);
    _delay_ms(100);
  }
  return 0;
}
