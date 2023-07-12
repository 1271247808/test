#include "stm32f10x.h"                  // Device header
#include "LED.h"
#include "Timer.h"
#include "Alarm.h"

/*选择模式：
0：停止;
1：绿灯间隔2秒闪烁;
2：蜂鸣器间隔一秒鸣响;
3：声光报警工作(红灯和蜂鸣器间隔一秒工作);
4：红灯间隔2秒闪烁;
5：红色灯闪间隔1秒;
6：//绿色灯闪间隔1秒;
*/

//uint16_t Num;
uint16_t Alarm_Key;

void Alarm_Init(void)
{
	Timer_Init();
	LED_Init();
	Buzzer_OFF();
}

void GREEN_ON(void)
{
	LED1_ON();
}

void GREEN_OFF(void)
{
	LED1_OFF();
}

void RED_ON(void)
{
	LED2_ON();
}

void RED_OFF(void)
{
	LED2_OFF();
}


void Alarm(void)
{
	if(Alarm_Key==0)
	{
		RED_OFF();
		GREEN_OFF();
		Buzzer_OFF();
	}
	else if(Alarm_Key==1)//绿色灯闪间隔2秒
	{
		if(Num==1||Num==4||Num==7||Num==10)
		{
			GREEN_ON();
		}
		else
		{
			GREEN_OFF();
		}
	}
	else if(Alarm_Key==2)//蜂鸣器间隔一秒鸣响
	{
		
		if(Num==1||Num==3||Num==5||Num==7||Num==9||Num==11)
		{
			Buzzer_ON();
		}
		else
		{
			Buzzer_OFF();
		}
	}
	else if(Alarm_Key==3)//声光报警工作
	{
		GREEN_OFF();
		if(Num==1||Num==3||Num==5||Num==7||Num==9||Num==11)
		{
			RED_ON();
			Buzzer_ON();
		}
		else if(Num==2||Num==4||Num==6||Num==8||Num==10||Num==12)
		{
			RED_OFF();
			Buzzer_OFF();
		}
	}
	else if(Alarm_Key==4)//红色灯闪间隔2秒
	{
		if(Num==1||Num==4||Num==7||Num==10)
		{
			RED_ON();
		}
		else
		{
			RED_OFF();
		}
	}
	else if(Alarm_Key==5)//红色灯闪间隔1秒
	{
		if(Num==1||Num==3||Num==5||Num==7||Num==9||Num==11)
		{
			RED_ON();
		}
		else
		{
			RED_OFF();
		}
	}
	else if(Alarm_Key==6)//绿色灯闪间隔1秒
	{
		if(Num==1||Num==3||Num==5||Num==7||Num==9||Num==11)
		{
			GREEN_ON();
		}
		else
		{
			GREEN_OFF();
		}
	}
}


