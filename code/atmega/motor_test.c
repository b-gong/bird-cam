#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "motor.h"

int main()
{
  motor_init();

  int degree = 180;

  while(1) {
    rotate(degree);
    _delay_ms(5000);
  }
  return 0;
}
