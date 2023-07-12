#include "stm32f10x.h"                  // Device header
#include  "Delay.h"

void LED_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14| GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOC, GPIO_Pin_13 | GPIO_Pin_14| GPIO_Pin_15);
}

void LED1_ON(void)//PC13:LED1:Green
{
	GPIO_ResetBits(GPIOC, GPIO_Pin_13);
}

void LED1_OFF(void)
{
	GPIO_SetBits(GPIOC, GPIO_Pin_13);
}

void LED1_Turn(void)
{
	if (GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_13) == 0)
	{
		GPIO_SetBits(GPIOC, GPIO_Pin_13);
	}
	else
	{
		GPIO_ResetBits(GPIOC, GPIO_Pin_13);
	}
}

void LED2_ON(void)//PC14:LED2:Red
{
	GPIO_ResetBits(GPIOC, GPIO_Pin_14);
}

void LED2_OFF(void)
{
	GPIO_SetBits(GPIOC, GPIO_Pin_14);
}

void LED2_Turn(void)
{
	if (GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_14) == 0)
	{
		GPIO_SetBits(GPIOC, GPIO_Pin_14);
	}
	else
	{
		GPIO_ResetBits(GPIOC, GPIO_Pin_14);
	}
}

void Buzzer_ON(void)//PC15:Buzzer
{
	GPIO_SetBits(GPIOC, GPIO_Pin_15);
}

void Buzzer_OFF(void)
{
	GPIO_ResetBits(GPIOC, GPIO_Pin_15);
}

void BuzzerOne(void)
{
	Buzzer_ON();
	Delay_ms(200);
	Buzzer_OFF();
}
