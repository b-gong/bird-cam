#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "HX711.h"

int main(void)
{
  DDRC |= 1 << DDC0;          // Set PORTC bit 0 for output

  // Init HX711
  HX711_init(128);
  HX711_set_scale(1.f/*242300.88*/);
  HX711_set_gain(128);
  HX711_tare(10);
  double tare_point_128 = HX711_get_offset();
  double calibration_128 = 222138.f;//220235.f;
  _delay_ms(500);

  double current_weight_128, previous_weight_128;

  current_weight_128 = HX711_read_average(10) - tare_point_128;
  current_weight_128 = current_weight_128/calibration_128;
  previous_weight_128 = current_weight_128;

  while(1)
  {   
    current_weight_128 = HX711_read_average(10) - tare_point_128;
    current_weight_128 = current_weight_128/calibration_128;

    if(current_weight_128 - previous_weight_128 > 100) {
      while (1) {
        PORTC |= 1 << PC0;      // Set PC0 to a 1
        _delay_ms(200);
        PORTC &= ~(1 << PC0);   // Set PC0 to a 0
      }

    }

    previous_weight_128 = current_weight_128;
  }
}
