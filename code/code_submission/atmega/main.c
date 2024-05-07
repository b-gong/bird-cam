#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "HX711_light.h"
#include "motor.h"
#include "i2c.h"

#define NIGHT(t) (t > 19 || t < 7)
#define NUM_REFILL 2
#define PIC_CD 65535 // 9.1 sec @ 7.3728 MHz / 1024

void init_timer(void);
void dispenseFood(void);
void blink(void);

volatile uint8_t pic_cd_flag = 0;
const uint8_t refill[NUM_REFILL] = {6, 18};

int main() {
  // indicator led init
  DDRC |= 1 << DDC0;

  // time init
  init_timer();
  sei();

  // uart init
  serial_init(MYUBRR);

  // esp32 reset pin init
  DDRD |= 1 << PD4;
  PORTD |= 1 << PD4;
  _delay_ms(50);
  PORTD &= ~(1 << PD4);
  _delay_ms(100);
  PORTD |= 1 << PD4;

  // HX711 init
  HX711_init();
  int32_t tare = readData();
  int32_t data = 0;

  // Motor init
  motor_init();

  // RTC init
  rtc_init2();
  // 12:00:00 Monday April 22 2024
  rtc_time rtc = { .sec = 40, .min = 59, .hour = 6, .weekDay = 2, .day = 22, .month = 4, .year = 24 };
  rtc_setTime(&rtc);

  // Nightlight init
  DDRB |= 1 << DDB1;

  // Already refilled flag
  uint8_t refilled = 0;

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

    // poll rtc
    rtc_gettime(&rtc);

    // if weight triggered, check rtc and send uart msg
    if(data - tare > 100000 && pic_cd_flag == 0) {
      blink();
      uint8_t msg[7] = {rtc.sec, rtc.min, rtc.hour, rtc.day, rtc.month, rtc.year, 0};
      serial_bufferout(msg);

      // 9.1 second cooldown
      pic_cd_flag = 1;
      TCNT1 = 0; // reset timer counter
      TCCR1B |= (1 << CS12 | 1 << CS10); // Set prescalar; start timer
    }


    // check nighttime
    if(NIGHT(rtc.hour))
      PORTB |= 1 << PB1;
    else
      PORTB &= ~(1 << PB1);

    // check fed
    uint8_t isRefillHour = 0;
    for(i = 0; i < NUM_REFILL; i++) {
      if(rtc.hour == refill[i]) {
        isRefillHour = 1;
        if(!refilled) {
          dispenseFood();
          refilled = 1;
        }
      }
    }
    if(!isRefillHour) refilled = 0;

    _delay_ms(1000);
  }
}

ISR(TIMER1_COMPA_vect) {
    TCCR1B &= ~(1 << CS12 | 1 << CS10); // stop timer
    pic_cd_flag = 0;
}

void dispenseFood() {
  rotate(60);
  _delay_ms(100);
  rotate(-60);
}

void init_timer() {
    TCCR1B |= (1 << WGM12); // CTC mode
    TCCR1B &= ~(1 << CS12 | 1 << CS10); // Set prescalar to 0; (7.3728 MHz/1024)
    TIMSK1 |= (1 << OCIE1A); // enable timer interrupt
    OCR1A = PIC_CD;
}

void blink() {
  PORTC |= 1 << PC0;      // Set PC0 to a 1
  _delay_ms(500);
  PORTC &= ~(1 << PC0);   // Set PC0 to a 0
}
