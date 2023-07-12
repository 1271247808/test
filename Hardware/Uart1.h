#ifndef __UART1_H
#define __UART1_H

#include "stm32f10x.h"

#define USART1_REC_LEN  128
#define USART1_SEND_LEN 128

void Usart1_Init(u32 Baudrate);
void Usart1_SendByte(uint8_t Data);
void Usart1_SendString(char* str);
void USART1_IRQHandler(void);
//void LEDcontrol(void);
void HMISends(char *buf1);
void HMISendb(u8 k);
void HMISendstart(void);
void HMISendCom(char *buf);
void HMISendVal(int val);
void HMISendTxt(char *txt);

#endif
