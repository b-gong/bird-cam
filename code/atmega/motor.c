#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "i2c.h"

void rotate(int degrees, int delay) {
    float steps = degrees * 2048.0 / 360;
    int step = 0;
    while(steps > 0) {
        if(step == 0) {
            PORTB |= (1<<PB2);
            PORTC &= ~((1<<PC1) | (1<<PC3));
            PORTC |= (1<<PC2);
        }
        else if(step == 1) {
            PORTB &= ~(1<<PB2);
            PORTC &= ~(1<<PC3);
            PORTC |= ((1<<PC2) | (1<<PC1));
        }
        else if(step == 2) {
            PORTB &= ~(1<<PB2);
            PORTC &= ~(1<<PC2);
            PORTC |= ((1<<PC3) | (1<<PC1));
        }
        else if(step == 3) {
            PORTB |= (1<<PB2);
            PORTC &= ~((1<<PC2) | (1<<PC1));
            PORTC |= (1<<PC3);
        }
        step = (step+1)%4;
        steps--;
        _delay_ms(10);
  }
}

int main()
{
    int degree = 180;
    int delay = 100;
    
    // Initialize DDR registers
    DDRC |= (1 << PC3) | (1 << PC2) | (1 << PC1); // PC1-PC3 and PB2 as output
    DDRB |= (1 << PB2);

    rtc_init2();
    rtc_setTime(0x19, 0x45, 0x30);
    
    unsigned char i, j, k;
    
    while(1) {
        rtc_gettime(&i, &j, &k);
        int second = k;

                
        if (second == 0) //spin every hour
        {
            rotate(degree, delay);
        }
        _delay_ms(5);
    }
    return 0;
}
