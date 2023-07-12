#ifndef __PID_H
#define __PID_H

#include "stm32f10x.h"                  // Device header

typedef struct
{
   	float kp,ki,kd;//三个系数
    float error,lastError;//误差、上次误差
    float integral,maxIntegral;//积分、积分限幅
    float output,maxOutput;//输出、输出限幅
}PID_InitTypedef;
 

void PID_Init(PID_InitTypedef *pid,float p,float i,float d,float maxI,float maxOut);
void PID_Calc(PID_InitTypedef *pid,float reference,float feedback);

void PID_Ahead(PID_InitTypedef *mypid);

extern PID_InitTypedef mPID;
#endif
