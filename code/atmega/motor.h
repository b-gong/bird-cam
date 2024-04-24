//
//  motor.h
//
//
//  Created by Chur Tam on 4/22/24.
//

#ifndef MOTOR_H
#define MOTOR_H

#define DELAY_MS 5
#define MOTOR_PHASES 4
#define STEP_NUM 8

void rotate(int degrees);
void motor_init();

// const int stepTable[STEP_NUM][MOTOR_PHASES] = {
// 	{1,0,0,1},
// 	{0,0,0,1},
// 	{0,0,1,1},
// 	{0,0,1,0},
//   {0,1,1,0},
//   {0,1,0,0},
//   {1,1,0,0},
//   {1,0,0,0}
// };

// const int stepTable[STEP_NUM][MOTOR_PHASES] = {
//   {1,0,1,0},
//   {0,1,1,0},
//   {0,1,0,1},
//   {1,0,0,1}
// };

#endif /* motor_h */
