#include "stm32f10x.h"
#include "Motor.h"
#include "PWM.h"
#include "Delay.h"
#include "Control.h"

void Car_Init(){
	Motor_Init_Right();
	Motor_Init_Left();
}

void Go_Ahead(){
	Motor_SetLeftSpeed(-Speed);
	Motor_SetRightSpeed(Speed);
}

void Go_Back(){
	Motor_SetLeftSpeed(Speed);
	Motor_SetRightSpeed(-Speed);
}

//void Turn_Left(){
//	Motor_SetLeftSpeed(0);
//	Motor_SetRightSpeed(Speed);
//}

//void Turn_Right(){
//	Motor_SetRightSpeed(0);
//	Motor_SetLeftSpeed(Speed);
//	
//}

void Self_Left(){
	Motor_SetLeftSpeed(-Speed);
	Motor_SetRightSpeed(-Speed);
}

void Self_Right(){
	Motor_SetLeftSpeed(Speed);
	Motor_SetRightSpeed(Speed);
}

void Car_Stop(){
	Motor_SetLeftSpeed(0);
	Motor_SetRightSpeed(0);
}

void Turn_Left(void){
	Self_Left();
	Delay_ms(495);
	Car_Stop();	
}

void Turn_Left2(void)
{	
	Motor_SetLeftSpeed(-Speed);
	Motor_SetRightSpeed(0);
	Delay_ms(890);
	Car_Stop();
}

void Turn_Right2(void)
{
	Motor_SetLeftSpeed(0);
	Motor_SetRightSpeed(Speed);
	Delay_ms(890);
	Car_Stop();
}

void Turn_Right(void){
		Self_Right();
		Delay_ms(495);
		Car_Stop();		
}

void Turn_Around(void){
		Self_Right();
		Delay_ms(890);
		Car_Stop();	
}

void Trace_Ahead(int8_t Speed, int8_t Turn)
{
	Motor_SetLeftSpeed(-(Speed-Turn));
	Motor_SetRightSpeed(Speed+Turn);
}