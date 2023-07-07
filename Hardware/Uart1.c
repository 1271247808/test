#include "stm32f10x.h"
#include "stdio.h"
#include "Delay.h"
#include "string.h"
#include "Uart1.h"
#include "Control.h"
#include "Uart3.h"

//UART1用于与串口屏连接

//Param_InitTypedef Param;

u8 USART1_RX_BUF[USART1_REC_LEN]={0};
u8 USART1_REC_CNT_LEN=0;

uint8_t LEDG_State = 0;
uint8_t LEDR_State = 0;

void Usart1_Init(u32 Baudrate)
{
	GPIO_InitTypeDef    GPIO_InitStructure;
	USART_InitTypeDef	USART_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	GPIO_PinRemapConfig(GPIO_Remap_USART1,ENABLE);			//引脚重映射
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;					//TXD-PB6
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_7;					//RXD-PB7
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate=Baudrate;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_Init(USART1, &USART_InitStructure);
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	USART_Cmd(USART1,ENABLE);
}

void Usart1_SendByte(uint8_t Data)
{
	USART_SendData(USART1,Data);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)==RESET);
}

void Usart1_SendString(char* str)
	{
		 while(* str)
		 {
			 while(USART_GetFlagStatus(USART1, USART_FLAG_TC)==RESET);
			 USART_SendData(USART1,* str++);
		 }
	}
	
void HMISends(char *buf1)		  //字符串发送函数
{
	u8 i=0;
	while(1)
	{
	 if(buf1[i]!=0)
	 	{
			USART_SendData(USART1,buf1[i]);  //发送一个字节
			while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET){};//等待发送结束
		 	i++;
		}
	 else	return;
	}
}

void HMISendb(u8 k)		         //字节发送函数
{		 
	u8 i;
	 for(i=0;i<3;i++)
	 {
	 if(k!=0)
	 	{
			USART_SendData(USART1,k);  //发送一个字节
			while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET){};//等待发送结束
		}
	 else	return;

	 } 
} 

void HMISendstart(void)
{
	 	Delay_ms(200);
		HMISendb(0xff);
		Delay_ms(200);
}

//先写unsigned char  buf[64]; sprintf((char *)buf,"pagex.xx.xx=%x",xx);
void HMISendCom(char *buf)
{
	HMISends(buf);
	HMISendb(0xff);	
}

void HMISendVal(int val)
{
	unsigned char  buf[64];
	sprintf((char *)buf,"task1.n0.val=%d",val); 		//强制类型转化，转化为字符串
	HMISends((char *)buf); 								//发送val的数据
	HMISendb(0xff);										//结束符
}

void HMISendTxt(char *txt)
{
	unsigned char  buf[64];
	sprintf((char *)buf,"tiaoshi.t2.txt=\"%s\"",txt);		//显示字符串
    HMISends((char *)buf);
	
    HMISendb(0xff);
}

void USART1_IRQHandler(void)
{
	u8 res;
	if(USART_GetITStatus(USART1,USART_IT_RXNE) != RESET)
	{	    
		res = USART_ReceiveData(USART1);
		
//		if((USART1_REC_CNT_LEN & 0x8000) == 0)
//		{
//			if(USART1_REC_CNT_LEN & 0x4000)
//			{
//				if(res != 0x0A)	USART1_REC_CNT_LEN = 0;
//				else USART1_REC_CNT_LEN |= 0x8000;
//			}
//			else
//			{
//				if(res == 0x0D)	USART1_REC_CNT_LEN |= 0x4000;
//				else
//				{
//					USART1_RX_BUF[USART1_REC_CNT_LEN & 0x3FFF] = res;	
//					USART1_REC_CNT_LEN++;
//					if(USART1_REC_CNT_LEN > USART1_REC_LEN)
//					{
//						USART1_REC_CNT_LEN=0;
//					}		
//				}
//			}
//		}
		
//		if(res == 0x1A)			LEDG_State = 1;	
//		else if(res == 0x1B)	LEDG_State = 0;
//		else if(res == 0x2A)	LEDR_State = 1;
//		else if(res == 0x2B)	LEDR_State = 0;
		if(res == 0x01)	
		{
			Param.ModeChoose = TASK1;	
			Usart3_SendString("mode11");
		}
		else if(res == 0x02)	
		{
			Param.ModeChoose = TASK2;	
			Usart3_SendString("mode11");
		}
		else if(res == 0x03)	
		{
			Param.ModeChoose = TASK3;	
			Usart3_SendString("mode4");
		}
		else if(res == 0x09)	
		{
			Param.ModeChoose = NotStarting;
		}
	}	 
}

//void LEDcontrol(void)
//{
//	if(USART1_RX_BUF[0] == 0x1A)
//	{
//		LEDG_State = 1;
//	}
//	else if(USART1_RX_BUF[0] == 0x1B)
//	{
//		LEDG_State = 0;
//	}
//	if(USART1_RX_BUF[0] == 0x2A)
//	{
//		LEDR_State = 1;
//	}
//	else if(USART1_RX_BUF[0] == 0x2B)
//	{
//		LEDR_State = 0;
//	}
//	USART1_REC_CNT_LEN=0; 
//	memset((char*)USART1_RX_BUF,0,128);
//}

