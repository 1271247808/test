#ifndef __ALARM_H
#define __ALARM_H
#include "stm32f10x.h"                  // Device header

void Alarm_Init(void);
void RED_ON(void);
void RED_OFF(void);
void GREEN_ON(void);
void GREEN_OFF(void);


void Alarm(void);
//中断蜂鸣器led功能

extern uint16_t Num;
extern uint16_t Alarm_Key;

#endif
