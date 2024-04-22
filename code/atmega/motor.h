//
//  motor.h
//  
//
//  Created by Chur Tam on 4/22/24.
//

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "i2c.h"

#ifndef motor_h
#define motor_h


#endif /* motor_h */

void motorSpinCW();
void rotate(int degrees, int delay);
int main();
