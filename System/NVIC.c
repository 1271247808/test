#include "stm32f10x.h"                  // Device header

void NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStruct;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
//	//PB14 红外中断
//	NVIC_InitStruct.NVIC_IRQChannel=EXTI15_10_IRQn;
//	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
//	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;
//	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;
//	NVIC_Init(&NVIC_InitStruct);
	
//	//PB3中断
//	NVIC_InitStruct.NVIC_IRQChannel=EXTI4_IRQn;
//	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
//	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;
//	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;
//	NVIC_Init(&NVIC_InitStruct);
	
	//Uart1中断
	NVIC_InitStruct.NVIC_IRQChannel=USART1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;		
	NVIC_Init(&NVIC_InitStruct);
	
	//Uart3中断
	NVIC_InitStruct.NVIC_IRQChannel=USART3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;		
	NVIC_Init(&NVIC_InitStruct);
}
