#ifndef __PWM_H
#define __PWM_H
#include "stm32f10x.h"                  // Device header

//void PWM_Init(void);
//void PWM_SetCompare1(uint16_t Compare);
void PWM_Init_Right(void);
void PWM_SetCompare_Right(uint16_t Compare);
void PWM_Init_Left(void);
void PWM_SetCompare_Left(uint16_t Compare);

#endif
