#ifndef _HX711_LIGHT_H
#define _HX711_LIGHT_H

#include <avr/io.h>

#define HX_DDR_DAT DDRD
#define HX_DDR_CLK DDRD
#define HX_DAT PD2
#define HX_CLK PD3
#define HX_PIN_DAT PIND
#define HX_PORT_CLK PORTD
#define READ_DAT ((HX_PIN_DAT & (1 << HX_DAT)) != 0)
#define CH 128
// #define CH 64
// #define CH 32

void HX711_init();
uint8_t dataReady();
int32_t readData();
void update(int32_t *result);
void setClk(uint8_t n);

#endif  // _HX711_LIGHT_H
