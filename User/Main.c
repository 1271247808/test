//Success at tracing and return

#include "stm32f10x.h"
#include "stdio.h"
#include "Delay.h"
#include "OLED.h"
//#include "LED.h"
#include "Uart1.h"
#include "Uart3.h"
#include "NVIC.h"
#include "Control.h"
#include "Car.h"
#include "PID.h"
#include "PWM.h"
#include "CountSensor.h"

u32 Screen_Baudrate = 9600;
u32 Vision_Baudrate = 115200;

int main(void)
{
	//LED_Init();
	OLED_Init();
	OLED_ShowString(1, 1, "Delta:");
	OLED_ShowString(2, 1, "PID:");
	Usart1_Init(Screen_Baudrate);
	Usart_Init(Vision_Baudrate);
	Car_Init();
	PID_Init(&mPID, 4, 0, 3, 10, 13);
	CountSensor_Init();
	NVIC_Config();
	
	while(Flag.Run_Step == 0)
	{
		while(Param.ModeChoose == NotStarting);
		Sensor_Count = 0;
		Flag.Run_Step = Goto;
//		Sensor_Count = 10;
//		Flag.Run_Step = GoBack;
	}
	
	while(1)
	{
		CarControl();
		//Go_Ahead();
		//Delay_ms(500);
//		Turn_Left();
//		//Turn_Left2();
//		Turn_Right();
//		//After left
//		//Go_Back();
//		Delay_ms(500);
	}
}
