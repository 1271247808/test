#include "stm32f10x.h"                  // Device header
#include "PWM.h"

//void Motor_Init(void)
//{
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//	
//	GPIO_InitTypeDef GPIO_InitStructure;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);
//	
//	PWM_Init();
//}

//void Motor_SetSpeed(int8_t Speed)
//{
//	if (Speed >= 0)
//	{
//		GPIO_SetBits(GPIOA, GPIO_Pin_4);
//		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
//		PWM_SetCompare1(Speed);
//	}
//	else
//	{
//		GPIO_ResetBits(GPIOA, GPIO_Pin_4);
//		GPIO_SetBits(GPIOA, GPIO_Pin_5);
//		PWM_SetCompare1(-Speed);
//	}
//}

void Motor_Init_Right(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	PWM_Init_Right();
}

void Motor_Init_Left(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_11 | GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	PWM_Init_Left();
}

void Motor_SetRightSpeed(int16_t Speed)
{
	if (Speed >= 0)
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_4);
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
		PWM_SetCompare_Left(Speed);
	}
	else
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_4);
		GPIO_SetBits(GPIOA, GPIO_Pin_5);
		PWM_SetCompare_Left(-Speed);
	}
}

void Motor_SetLeftSpeed(int16_t Speed)
{
	if (Speed >= 0)
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_11);
		GPIO_ResetBits(GPIOA, GPIO_Pin_12);
		PWM_SetCompare_Right(Speed);
	}
	else
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_11);
		GPIO_SetBits(GPIOA, GPIO_Pin_12);
		PWM_SetCompare_Right(-Speed);
	}
}
