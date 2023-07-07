#ifndef __CONTROL_H
#define __CONTROL_H

#include "stm32f10x.h"

void CarControl(void);
void MotorControl(uint16_t speed);

#define NotStarting 0
#define TASK1		1
#define TASK2		2
#define TASK3 		3

#define Goto		4
#define LCorner		5
#define GoBack		6
#define RCorner		7
#define Over 		8

typedef struct{	
	float 		Servo_Speed;
	float 		Servo_Target_Position;
	float 		Servo_Target_Val;
	int   		Motor1_PWM_Out;
	int  		Motor2_PWM_Out;
	uint8_t 	Vision_Data;
	uint16_t 	Timer_threshold_value;
	uint8_t 	ModeChoose;
	
	short UnitTime_Motor1Pluse;
	short UnitTime_Motor2Pluse;
}Param_InitTypedef;

typedef struct{	
	uint8_t Is_Go_straight;
	uint8_t Is_Stop_Car;
	uint8_t Is_Turn_Car;
	uint8_t Is_Timer_Up;
	uint8_t Is_Reverse;
	uint8_t Run_Step;
	uint8_t Start_Count;
}Flag_InitTypedef;

extern Param_InitTypedef Param;
extern Flag_InitTypedef Flag;
extern int16_t Speed;

//extern int PID_actual_angle;
extern int Corner_Flag;

#endif
