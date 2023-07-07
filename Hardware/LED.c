#include "stm32f10x.h"
#include "LED.h"

int LEDGState = 0;

void LED_Init(void){
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);		//PB3 PB4需要重映射为普通I/O引脚
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	DBGMCU->CR &= ~((uint32_t)1<<5);							//PB3需要关闭异步跟踪功能
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
}

void LEDG_OFF(void){
	GPIO_ResetBits(GPIOB, GPIO_Pin_3);
}

void LEDG_ON(void){
	GPIO_SetBits(GPIOB, GPIO_Pin_3);
}

void LEDR_OFF(void){
	GPIO_ResetBits(GPIOB, GPIO_Pin_4);
}

void LEDR_ON(void){
	GPIO_SetBits(GPIOB, GPIO_Pin_4);
}

void LEDSwitch(void)
{
	if(LEDG_State == 1)	LEDG_ON();
	else if(LEDG_State == 0) LEDG_OFF();
	
	if(LEDR_State == 1)	LEDR_ON();
	else if(LEDR_State == 0) LEDR_OFF();
}
