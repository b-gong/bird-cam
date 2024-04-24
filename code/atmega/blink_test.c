#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
  DDRB |= 1 << DDB1;          // Set PORTC bit 0 for output

  while(1)
  {
    PORTB |= 1 << PB1;      // Set PC0 to a 1
    _delay_ms(500);
    PORTB &= ~(1 << PB1);   // Set PC0 to a 0
    _delay_ms(500);
  }
}
