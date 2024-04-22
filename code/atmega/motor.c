#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include "motor.h"

void rotate(int degrees) {
  float steps = abs(degrees) / 360;
  steps *= 2048;
  static int step = 0;
  
  while(steps > 0) {
    if(step == 0) {
      PORTB |= (1<<PB2);
      PORTC &= ~((1<<PC1) | (1<<PC3));
      PORTC |= (1<<PC2);
    }
    else if(step == 1) {
      PORTB &= ~(1<<PB2);
      PORTC &= ~(1<<PC3);
      PORTC |= ((1<<PC2) | (1<<PC1));
    }
    else if(step == 2) {
      PORTB &= ~(1<<PB2);
      PORTC &= ~(1<<PC2);
      PORTC |= ((1<<PC3) | (1<<PC1));
    }
    else if(step == 3) {
      PORTB |= (1<<PB2);
      PORTC &= ~((1<<PC2) | (1<<PC1));
      PORTC |= (1<<PC3);
    }

    if(degrees > 0) step = (step+1)%4;
    else if(degrees < 0) step = (step-1)%4;
    steps--;
    _delay_ms(DELAY_MS);
  }
}

void motor_init()
{
  // Initialize DDR registers
  DDRC |= (1 << PC3) | (1 << PC2) | (1 << PC1); // PC1-PC3 and PB2 as output
  DDRB |= (1 << PB2);
}