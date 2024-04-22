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

void i2c_write(unsigned char data)
{
  TWDR = data;
  TWCR = (1 << TWINT) | (1 << TWEN);
  while ((TWCR & (1 << TWINT)) == 0);
}

unsigned char i2c_read(unsigned char ackVal)
{
  TWCR = (1 << TWINT) | (1 << TWEN) | (ackVal << TWEA);
  while ((TWCR & (1 << TWINT)) == 0);
  return TWDR;
}

void i2c_stop(){
  TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
  for (int x = 0; x < 100; x++); //wait for some time
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

void rtc_setTime(char s, char m, char h, char wd, char d, char mo, char y)
{
  i2c_start();
  i2c_write(0xD0);
  i2c_write(0x00);
  i2c_write(s);
  i2c_write(m);
  i2c_write(h);
  i2c_write(wd);
  i2c_write(d);
  i2c_write(mo);
  i2c_write(y);
  i2c_stop();
}

void rtc_gettime(unsigned char *h, unsigned char *m, unsigned char *s)
{
  i2c_start();
  i2c_write(0xD0);
  i2c_write(0x00);
  i2c_stop();

  i2c_start();
  i2c_write(0xD1);
  *s = i2c_read(1);
  *m = i2c_read(1);
  *h = i2c_read(0);
}
