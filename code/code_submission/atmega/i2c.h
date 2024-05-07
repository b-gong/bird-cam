//
//  i2c.h
//
//
//  Created by Chur Tam on 4/22/24.
//

#ifndef I2C_H
#define I2C_H

typedef struct {
  uint8_t sec;
  uint8_t min;
  uint8_t hour;
  uint8_t weekDay;
  uint8_t day;
  uint8_t month;
  uint8_t year;
} rtc_time;

void i2c_init(void);
void i2c_start(void);
void i2c_write(uint8_t data);
uint8_t i2c_read(uint8_t ackVal);
void i2c_stop(void);
void rtc_init2(void);
void rtc_setTime(rtc_time *rtc);
void rtc_gettime(rtc_time *rtc);

#endif /* i2c_h */
