#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#include "i2c.h"

int main() {
  serial_init(MYUBRR);

  // RTC init
  rtc_init2();
  // 12:00:00 Monday April 22 2024
  rtc_time rtc = { .sec = 0, .min = 0, .hour = 0, .weekDay = 2, .day = 22, .month = 4, .year = 24 };
  rtc_setTime(&rtc);

  while(1) {
    rtc_gettime(&rtc);

    uint8_t output[7] = {rtc.sec, rtc.min, rtc.hour, rtc.day, rtc.month, rtc.year, 0};

    serial_bufferout(output);

    _delay_ms(1000);
  }
}
