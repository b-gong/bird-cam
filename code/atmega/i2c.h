//
//  i2c.h
//  
//
//  Created by Chur Tam on 4/22/24.
//

#ifndef I2C_H
#define I2C_H 

void i2c_init(void);
void i2c_start(void);
void i2c_write(unsigned char data);
unsigned char i2c_read(unsigned char ackVal);
void i2c_stop(void);
void rtc_init2(void);
void rtc_setTime(unsigned char h, unsigned char m, unsigned char s);
void rtc_gettime(unsigned char *h, unsigned char *m, unsigned char *s);

#endif /* i2c_h */
