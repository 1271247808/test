#ifndef __UART3_H
#define __UART3_H

#include "stm32f10x.h"

#define USART3_REC_LEN  128
#define USART3_SEND_LEN 128

void Usart_Init(u32 Baudrate);
void Usart3_SendByte(uint8_t Data);
void Usart3_SendString(char* str);
void USART3_IRQHandler(void);
void Wait_Vision(void);

extern short PID_actual_angle;
extern int Corner_Flag;

extern u8 RxCounter1;
extern u8 RxBuffer1[10];
extern u8 RxState;
extern u8 RxFlag1;
	
#endif
