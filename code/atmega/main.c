#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#include "HX711.h"
#include "motor.h"

int main() {
  // uart init
  uart_init();

  // HX711 init
  HX711_init(128);
  HX711_set_scale(1.f/*242300.88*/);
  HX711_set_gain(128);
  HX711_tare(10);
  double tare_point_128 = HX711_get_offset();
  double calibration_128 = 222138.f;//220235.f;

  double current_weight_128, previous_weight_128;

  // Motor init
  motor_init();


  // RTC init
  rtc_init2();
  rtc_setTime(0x19, 0x45, 0x30);

  unsigned char h, m, s;
  
  // Init delay to make sure everything works right
  _delay_ms(500);

  /* Main loop
    * Weight sensor trigger (less or equal to interrupt?) -> check rtc -> send UART tx
    * rtc reaches scheduled time -> trigger motors
    * rtc reaches night time -> turn on nightlight
    * rtc reaches morning -> turn off nightlight``
  */
  while(1) {
    rtc_gettime(&h, &m, &s);
    int u = uart_tx();

    _delay_ms(2000);
  }
}
