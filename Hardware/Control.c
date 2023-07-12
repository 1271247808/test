#include "stm32f10x.h"                  // Device header
#include "Control.h"
#include "Delay.h"
#include "Uart3.h"
#include "PID.h"
#include "CountSensor.h"
#include "Car.h"
#include "OLED.h"
#include "LED.h"
#include "Alarm.h"

Param_InitTypedef Param;
Flag_InitTypedef Flag;

//int Sensor_Count;
//int16_t Speed = 15;
PID_InitTypedef mPID;

int i;

void CarControl(void)
{
	//TASK1
	if(Param.ModeChoose == TASK1)
	{
		Alarm_Key = 1;
		//Goto the end
		if(Flag.Run_Step == Goto)
		{	
			//reach the end
			if(Sensor_Count == 25)			//Return at box #25
			{
				Usart3_SendString("mode0");
				//Stop and Reverse
				Go_Ahead();
				Delay_ms(500);
				OLED_ShowString(3, 1, "Spin");
				Car_Stop();
				//Buzz
				BuzzerOne();
				Delay_ms(5000);
				//Flag.Is_Go_straight = 0;//Stop
				//Turn_Around();			//Reverse
				Corner_Flag = 3;
				Self_Left();
				Delay_ms(600);
				Usart3_SendString("mode2");
				while(Corner_Flag == 3)
				{
					Self_Left();
				}
				Corner_Flag = 0;
				Flag.Run_Step = GoBack;
				Flag.Is_Go_straight = 1;//Go
				Sensor_Count ++;
			}
			
			//PID Straight line
			else if(Corner_Flag == 0)
			{
				Flag.Run_Step = Goto;
				Flag.Is_Go_straight = 1;
				OLED_ShowString(3, 1, "Goto");
			}
			
			//detect left corner
			else if(Corner_Flag == 1)
			{
				Flag.Run_Step = LCorner;
				Flag.Is_Go_straight = 0;
				//Car_Stop();
			}
		}
		
		//execute left turn
		else if(Flag.Run_Step == LCorner)
		{
			OLED_ShowString(3, 1, "Left");
			//Usart3_SendString("mode0");
			Go_Ahead();
			Delay_ms(250);
			Car_Stop();
			Delay_ms(500);
			//Turn Left
			//Turn_Left();
			//Go_Ahead();
			//After left
			//Delay_ms(500);
			//for(i = 0 ; i < 5 ; i ++ )
			//{
			//Usart3_SendString("mode11");
			//}
			while(Corner_Flag == 1)
			{
				Self_Left();
			}
			
			Flag.Run_Step = Goto;
			Corner_Flag = 0;
			
		}
		
		//go back to the start
		else if(Flag.Run_Step == GoBack)
		{
			if(Sensor_Count == 26)
			{
				Sensor_Count--;
				Usart3_SendString("mode12");
			}
			//reach the start
			if(Sensor_Count == 0)
			{
				//Stop
				Flag.Is_Go_straight = 0;//Stop
				Usart3_SendString("mode0");	
				Go_Ahead();
				Delay_ms(500);
				Car_Stop();	
				//LED off
				Alarm_Key = 0;
				Car_Stop();	
				Flag.Run_Step = Over;
			}
			//PID Straight line
			else if(Corner_Flag == 0)
			{
				Flag.Run_Step = GoBack;
				Flag.Is_Go_straight = 1;
				
			}
			//dectect right corner
			else if(Corner_Flag == 2)
			{
				Flag.Run_Step = RCorner;
				Flag.Is_Go_straight = 0;
			}
			
		}
		//execute right turn
		else if(Flag.Run_Step == RCorner)
		{
			//Usart3_SendString("mode0");
			Go_Ahead();
			Delay_ms(250);
			Car_Stop();
			Delay_ms(500);
			//Turn Left
			//Turn_Right();
			//Go_Ahead();
			//After left
			//Delay_ms(500);
			//for(i = 0 ; i < 5 ; i ++ )
			//{
				//Usart3_SendString("mode12");
			//}
			Self_Right();
			Delay_ms(1000);
			Corner_Flag = 2;
			while(Corner_Flag == 2)
			{
				Self_Right();
			}
			Flag.Run_Step = GoBack;
			Corner_Flag = 0;
		}
		else
		{
			OLED_ShowString(3, 1, "GoBack");
		}
	}
	
	//TASK2
	else if(Param.ModeChoose == TASK2)
	{
		if(Flag.Run_Step == Goto)
		{
			//Reach #10
			if(Sensor_Count == 10)
			{
				//Alarm on
				//GLED off
				Alarm_Key = 3;
			}
			
			if(Sensor_Count == 15)
			{
				Flag.Run_Step = GoBack;
				//Flag.Is_Go_straight = 0;
				Usart3_SendString("mode12");	
				//Go_Ahead();
			}
			
			else if(Corner_Flag == 0)
			{
				//Alarm_Key = 1;
				if(Sensor_Count >= 10)
				{
					Alarm_Key = 3;
				}
				else if(Sensor_Count < 10)
				{
					Alarm_Key = 1;
				}
				Flag.Run_Step = Goto;
				Flag.Is_Go_straight = 1;
			}
			
			//detect left corner
			else if(Corner_Flag == 1)
			{
				//Alarm_Key = 1;
				Flag.Run_Step = LCorner;
				Flag.Is_Go_straight = 0;
				//Car_Stop();
			}
			
		}
		
		else if(Flag.Run_Step == LCorner)
		{
			//Usart3_SendString("mode0");
			Go_Ahead();
			Delay_ms(250);
			Car_Stop();
			Delay_ms(500);
			//Turn Left
			//Turn_Left();
			//Go_Ahead();
			//After left
			//Delay_ms(500);
			//for(i = 0 ; i < 5 ; i ++ )
			//{
			//Usart3_SendString("mode11");
			//}
			while(Corner_Flag == 1)
			{
				Self_Left();
			}
			
			Flag.Run_Step = Goto;
			Corner_Flag = 0;
			
		}
		
		else if(Flag.Run_Step == GoBack)
		{
			//reach the start
			if(Sensor_Count == 18)
			{
				//Stop
				Usart3_SendString("mode0");	
				Flag.Is_Go_straight = 0;//Stop
				Go_Ahead();
				Delay_ms(500);
				Car_Stop();	
				//LED off
				Alarm_Key = 0;
				Car_Stop();	
				Flag.Run_Step = Over;
			}
			
			else if(Sensor_Count == 15)
			{
				Flag.Is_Go_straight = 1;
			}
			
			//PID Straight line
			else if(Corner_Flag == 0)
			{
				Flag.Run_Step = GoBack;
				Flag.Is_Go_straight = 1;
				
			}
			//dectect right corner
			else if(Corner_Flag == 2)
			{
				Flag.Run_Step = RCorner;
				Flag.Is_Go_straight = 0;
			}
			
		}
		
		//execute right turn
		else if(Flag.Run_Step == RCorner)
		{
			//Usart3_SendString("mode0");
			Go_Ahead();
			Delay_ms(250);
			Car_Stop();
			Delay_ms(500);
			//Turn Left
			//Turn_Right();
			//Go_Ahead();
			//After left
			//Delay_ms(500);
			//for(i = 0 ; i < 5 ; i ++ )
			//{
				//Usart3_SendString("mode12");
			//}
			while(Corner_Flag == 2)
			{
				Self_Right();
			}
			Flag.Run_Step = GoBack;
			Corner_Flag = 0;
		}
	}
	
	else if(Param.ModeChoose == TASK3)
	{
		
	}
}
