//
//  i2c.h
//  
//
//  Created by Chur Tam on 4/22/24.
//

#ifndef i2c_h
#define i2c_h


#endif /* i2c_h */

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#ifndef i2c_h
#define i2c_h


#endif /* i2c_h */

void i2c_init(void);
void i2c_start(void);
void i2c_write(unsigned char data);
unsigned char i2c_read(unsigned char ackVal);
void i2c_stop();
void rtc_init2(void);
void rtc_setTime(unsigned char h, unsigned char m, unsigned char s);
void rtc_gettime(unsigned char *h, unsigned char *m, unsigned char *s);
