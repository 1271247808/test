#include "stm32f10x.h"                  // Device header
#include "Control.h"
#include "Uart3.h"
#include "PID.h"
#include "CountSensor.h"
#include "Car.h"

Param_InitTypedef Param;
Flag_InitTypedef Flag;

//int Sensor_Count;
int16_t Speed = 15;
PID_InitTypedef mPID;

void CarControl(void)
{
	if(Param.ModeChoose == TASK1)
	{
		if(Flag.Run_Step == Goto)
		{	
			//PID Straight line
			if(Corner_Flag == 0)
			{
				Flag.Run_Step = Goto;
				Flag.Is_Go_straight = 1;
			}
			
			else if(Corner_Flag == 1)
			{
				Flag.Run_Step = LCorner;
				Flag.Is_Go_straight = 0;
				Car_Stop();
			}
			
			if(Sensor_Count == 25)
			{
				//Stop and Reverse
				Flag.Is_Go_straight = 0;//Stop
				Turn_Around();			//Reverse
				Usart3_SendString("mode12");
				Flag.Run_Step = GoBack;
			}
		}
		
		else if(Flag.Run_Step == LCorner)
		{
			//Turn Left
//			Turn_Left2();
//			//After left
//			Usart3_SendString("mode11");
//			Flag.Run_Step = Goto;
//			Corner_Flag = 0;
			Car_Stop();
		}
		
		if(Flag.Run_Step == GoBack)
		{
			//PID Straight line
			if(Corner_Flag == 0)
			{
				Flag.Run_Step = GoBack;
				Flag.Is_Go_straight = 1;
				
			}
			else if(Corner_Flag == 2)
			{
				Flag.Run_Step = RCorner;
				Flag.Is_Go_straight = 0;
			}
			if(Sensor_Count == 0)
			{
				//Stop and Reverse
				Flag.Is_Go_straight = 0;//Stop
										
				Flag.Run_Step = Over;
			}
		}
		
		else if(Flag.Run_Step == RCorner)
		{
			//Turn Right
			Turn_Right2();	
			//After Right
			Usart3_SendString("mode12");
			Flag.Run_Step = GoBack;
			Corner_Flag = 0;
		}
	}
	
	else if(Param.ModeChoose == TASK2)
	{
		
	}
	
	else if(Param.ModeChoose == TASK3)
	{
		
	}
}
