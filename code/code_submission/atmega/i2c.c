//
//  i2c.h
//
//
//  Created by Chur Tam on 4/22/24.
//
// help from https://www.youtube.com/watch?v=4GKbIPlvCrY&t=77s

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "i2c.h"

void i2c_init(void)
{
  TWSR = 0x00;
  TWBR = 0x48; //set i2c clock to be 100khz crystal freq = 16Mhz
  TWCR = 0x04;
}

void i2c_start(void)
{
  TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
  while ((TWCR & (1 << TWINT)) == 0);
}

void i2c_write(uint8_t data)
{
  TWDR = data;
  TWCR = (1 << TWINT) | (1 << TWEN);
  while ((TWCR & (1 << TWINT)) == 0);
}

uint8_t i2c_read(uint8_t ackVal)
{
  TWCR = (1 << TWINT) | (1 << TWEN) | (ackVal << TWEA);
  while ((TWCR & (1 << TWINT)) == 0);
  return TWDR;
}

void i2c_stop(){
  TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
  int x;
  for (x = 0; x < 100; x++); //wait for some time
}

void rtc_init2(void)
{
  i2c_init();
  i2c_start();
  i2c_write(0xD0);
  i2c_write(0x07);
  i2c_write(0x00);
  i2c_stop();
}

void rtc_setTime(rtc_time *rtc)
{
  i2c_start();
  i2c_write(0xD0);
  i2c_write(0x00);
  i2c_write(rtc->sec);
  i2c_write(rtc->min);
  i2c_write(rtc->hour);
  i2c_write(rtc->weekDay);
  i2c_write(rtc->day);
  i2c_write(rtc->month);
  i2c_write(rtc->year);
  i2c_stop();
}

void rtc_gettime(rtc_time *rtc)
{
  i2c_start();
  i2c_write(0xD0);
  i2c_write(0x00);
  i2c_stop();

  i2c_start();
  i2c_write(0xD1);
  rtc->sec = i2c_read(1);
  rtc->min = i2c_read(1);
  rtc->hour = i2c_read(1);
  rtc->weekDay = i2c_read(1);
  rtc->day = i2c_read(1);
  rtc->month = i2c_read(1);
  rtc->year = i2c_read(0);
  i2c_stop();
}
