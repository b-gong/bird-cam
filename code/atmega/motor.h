//
//  motor.h
//  
//
//  Created by Chur Tam on 4/22/24.
//

#ifndef MOTOR_H
#define MOTOR_H

#define DELAY_MS 10
#define MOTOR_PHASES 4
#define STEP_NUM 4

void rotate(int degrees);
void motor_init();

// const int stepTable[MOTOR_PHASES][STEP_NUM] = {
//   {1,0,0,0},
//   {1,1,0,0},
//   {0,1,0,0},
//   {0,1,1,0},
// 	{0,0,1,0},
// 	{0,0,1,1},
// 	{0,0,0,1},
// 	{1,0,0,1}
// };

const int stepTable[MOTOR_PHASES][STEP_NUM] = {
  {1,0,1,0},
  {0,1,1,0},
  {0,1,0,1},
  {1,0,0,1}
};

#endif /* motor_h */
