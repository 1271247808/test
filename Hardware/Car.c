#include "stm32f10x.h"
#include "Motor.h"
#include "PWM.h"
#include "Delay.h"
#include "Control.h"

int16_t Speed = 30;
int16_t lspeed = 10;
int16_t rspeed = 10;

void Car_Init(){
	Motor_Init_Right();
	Motor_Init_Left();
}

void Go_Ahead(){
	Motor_SetLeftSpeed(Speed);
	Motor_SetRightSpeed(Speed);
}

void Go_Back(){
	Motor_SetLeftSpeed(-Speed);
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
	Motor_SetLeftSpeed(-lspeed);
	Motor_SetRightSpeed(lspeed);
}

void Self_Right(){
	Motor_SetLeftSpeed(rspeed);
	Motor_SetRightSpeed(-rspeed);
}

void Car_Stop(){
	Motor_SetLeftSpeed(0);
	Motor_SetRightSpeed(0);
}

void Turn_Left(void){
	Self_Left();
	Delay_ms(650);
	Car_Stop();	
	Delay_ms(100);
}

void Turn_Right2(void)
{	
	Motor_SetLeftSpeed(-Speed);
	Motor_SetRightSpeed(0);
	Delay_ms(890);
	Car_Stop();
}

void Turn_Left2(void)
{
	Motor_SetLeftSpeed(0);
	Motor_SetRightSpeed(Speed);
	Delay_ms(1000);
	Car_Stop();
}

void Turn_Right(void){
		Self_Right();
		Delay_ms(750);
		Car_Stop();	
		Delay_ms(100);
}

void Turn_Around(void){
		Self_Right();
		Delay_ms(1350);
		Car_Stop();
		Delay_ms(100);
}

void Trace_Ahead(int8_t Speed, int8_t Turn)
{
	Motor_SetLeftSpeed(Speed-Turn);
	Motor_SetRightSpeed(Speed+Turn);
}
