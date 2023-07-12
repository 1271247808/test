#ifndef __MOTOR_H
#define __MOTOR_H

#include "stm32f10x.h"                  // Device header

//void Motor_Init(void);
//void Motor_SetSpeed(int8_t Speed);
void Motor_Init_Right(void);
void Motor_Init_Left(void);
void Motor_SetRightSpeed(int8_t Speed);
void Motor_SetLeftSpeed(int8_t Speed);

#endif
