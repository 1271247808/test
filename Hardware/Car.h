#ifndef __CAR_H
#define __CAR_H

#include "stm32f10x.h"

void Car_Init(void);
void Self_Right(void);
void Self_Left(void);
void Turn_Right(void);
void Turn_Left(void);
void Go_Back(void);
void Go_Ahead(void);
void Car_Stop(void);
void Trace_Ahead(int8_t Speed,int8_t Turn);
void Turn_Left2(void);
void Turn_Right2(void);
void Turn_Around(void);

#endif
