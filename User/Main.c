//Success at tracing ong the straight line and stop at the corner

#include "stm32f10x.h"
#include "stdio.h"
#include "Delay.h"
#include "OLED.h"
#include "LED.h"
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
	PID_Init(&mPID, 1.0, 0, 3.0, 10, 5);
	
	NVIC_Config();
	
	while(Flag.Run_Step == 0)
	{
		while(Param.ModeChoose == NotStarting);
		Sensor_Count = 0;
		Flag.Run_Step = Goto;
	}
	
	while(1)
	{
		CarControl();
	}
}
