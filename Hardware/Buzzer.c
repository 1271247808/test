#include "stm32f10x.h"                  // Device header
#include "Delay.h"

void Buzzer_Init(void){
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void Buzzer_On(void){

	GPIO_SetBits(GPIOB, GPIO_Pin_0);
}

void Buzzer_Off(void){
	
	GPIO_ResetBits(GPIOB, GPIO_Pin_0);
}

void Buzz_300ms(void)
{
	Buzzer_On();
	Delay_ms(300);
	Buzzer_Off();
}
