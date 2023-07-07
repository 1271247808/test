#include "stm32f10x.h"                  // Device header
#include "Control.h"
#include "Delay.h"
#include "Uart3.h"
#include "PID.h"
#include "CountSensor.h"
#include "Car.h"

Param_InitTypedef Param;
Flag_InitTypedef Flag;

//int Sensor_Count;
//int16_t Speed = 15;
PID_InitTypedef mPID;

int i;

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
				//Car_Stop();
			}
			
			if(Sensor_Count == 16)			//Return at box #16
			{
				Usart3_SendString("mode0");
				//Stop and Reverse
				Delay_ms(600);
				Car_Stop();
				Delay_ms(300);
				Flag.Is_Go_straight = 0;//Stop
				Turn_Around();			//Reverse
				Flag.Run_Step = GoBack;
				Flag.Is_Go_straight = 1;//Go
				Sensor_Count ++;
			}
		}
		
		else if(Flag.Run_Step == LCorner)
		{
			Usart3_SendString("mode0");
			Go_Ahead();
			Delay_ms(600);
			Car_Stop();
			//Turn Left
			Turn_Left();
			//Go_Ahead();
			//After left
			//Delay_ms(500);
			//for(i = 0 ; i < 5 ; i ++ )
			//{
				Usart3_SendString("mode11");
			//}
			Flag.Run_Step = Goto;
			Corner_Flag = 0;
			
		}
		
		if(Flag.Run_Step == GoBack)
		{
			if(Sensor_Count == 17)
			{
				Sensor_Count--;
				Usart3_SendString("mode12");
			}
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
				//Stop
				Flag.Is_Go_straight = 0;//Stop
				Car_Stop();	
				//for(i = 0 ; i < 5 ; i ++ )
				//{
					Usart3_SendString("mode0");	
				//}		
				Car_Stop();	
				Flag.Run_Step = Over;
			}
		}
		
		else if(Flag.Run_Step == RCorner)
		{
			Usart3_SendString("mode0");
			Go_Ahead();
			Delay_ms(600);
			Car_Stop();
			//Turn Left
			Turn_Right();
			//Go_Ahead();
			//After left
			//Delay_ms(500);
			//for(i = 0 ; i < 5 ; i ++ )
			//{
				Usart3_SendString("mode12");
			//}
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
