#include "stm32f10x.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "Uart3.h"
#include "Control.h"
#include "PID.h"
#include "OLED.h"

//Param_InitTypedef Param;

short PID_actual_angle = 0;
int Corner_Flag = 0;

u8 RxCounter1 = 0;
u8 RxBuffer1[10] = {0};
u8 RxState = 0;
u8 RxFlag1 = 0;

//PID_InitTypedef mPID;
//int16_t Speed;

u8 USART3_RX_BUF[USART3_REC_LEN]={0};
u8 USART3_REC_CNT_LEN=0;

void Usart_Init(u32 Baudrate)
{
	GPIO_InitTypeDef    GPIO_InitStructure;
	USART_InitTypeDef	USART_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;//TXD-PB10
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;//RXD-PB11
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;	
	//GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate=Baudrate;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_Init(USART3, &USART_InitStructure);
	
	USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);
	USART_Cmd(USART3,ENABLE);
	USART_ClearFlag(USART3, USART_FLAG_TC);
}

void Usart3_SendByte(uint8_t Data)
{
	USART_SendData(USART3,Data);
	while(USART_GetFlagStatus(USART3, USART_FLAG_TXE)==RESET);
}

void Usart3_SendString(char* str)
	{
		 while(* str)
		 {
			 while(USART_GetFlagStatus(USART3, USART_FLAG_TC)==RESET);
			 USART_SendData(USART3,* str++);
		 }
	}
/*
void USART3_IRQHandler(void)
{
	u8 res;
	if(USART_GetITStatus(USART3,USART_IT_RXNE) != RESET)
	{	    
		res = USART_ReceiveData(USART3);
		if((USART3_REC_CNT_LEN & 0x8000) == 0)
		{
			if(USART3_REC_CNT_LEN & 0x4000)
			{
				if(res != 0x0A)	USART3_REC_CNT_LEN = 0;
				else USART3_REC_CNT_LEN |= 0x8000;
			}
			else
			{
				if(res == 0x0D)	USART3_REC_CNT_LEN |= 0x4000;
				else
				{
					USART3_RX_BUF[USART3_REC_CNT_LEN & 0x3FFF] = res;	
					USART3_REC_CNT_LEN++;
					if(USART3_REC_CNT_LEN > USART3_REC_LEN)
					{
						USART3_REC_CNT_LEN=0;
					}		
				}
			}
		}
	}	 
}

void Wait_Vision(void)
{
	//if(strstr((const char*)USART3_RX_BUF,"end")!=NULL)
	//{
		if(USART3_RX_BUF[0] == 0x31)
		{
			Param.Vision_Data=1;
			//Buzz_300ms();
		}
		USART3_REC_CNT_LEN=0; 
		memset((char*)USART3_RX_BUF,0,128);
	//}
}
*/

void USART3_IRQHandler(void)
{
	u8 com_data; 
	u8 i;
	u8 c1,c2;
//	char intc[6];
//	static u8 RxCounter1=0;
//	static u8 RxBuffer1[10]={0};
//	static u8 RxState = 0;	
//	static u8 RxFlag1 = 0;

	if(USART_GetITStatus(USART3,USART_IT_RXNE) != RESET)  	   //接收中断  
	{
		USART_ClearITPendingBit(USART3,USART_IT_RXNE);   //清除中断标志
		com_data = USART_ReceiveData(USART3);	
		
//		OLED_ShowSignedNum(2, 1, RxState, 4);
		
		//Receive PID data
		if(RxState==0 && com_data==0xBA)  //0xBA帧头
		{
			RxState=1;
			RxBuffer1[RxCounter1]=com_data;
			RxCounter1++;
		}
		
		else if(RxState==1 && com_data==0xBB)  //0xBB帧头
		{
			RxState=2;
			RxBuffer1[RxCounter1]=com_data;
			RxCounter1++;
		}
		
		else if(RxState==2)
		{
			RxBuffer1[RxCounter1]=com_data;
			RxCounter1++;
			if(RxCounter1 == 4)       //RxBuffer1接受满了,接收数据结束
			{
				RxState=3;
				RxFlag1=1;	
//				OLED_ShowSignedNum(3, 1, 2, 1);
			}
		}
		
		else if(RxState==3)		//检测是否接受到结束标志
		{
			RxBuffer1[RxCounter1]=com_data;
			//RxCounter1++;
			if(RxBuffer1[RxCounter1] == 0x5B)
			{
				USART_ITConfig(USART3,USART_IT_RXNE,DISABLE);//关闭DTSABLE中断
				if(RxFlag1)
				{
					c1 = RxBuffer1[RxCounter1 - 1];
					c2 = RxBuffer1[RxCounter1 - 2];
//					sprintf(intc, "%x%x\0", c1, c2);
//					PID_actual_angle = strtol(intc, 0, 8);
					PID_actual_angle = (c1 << 8) | c2;
					OLED_ShowSignedNum(1, 7, PID_actual_angle, 4);
					
					//PID_actual_angle = RxBuffer1[RxCounter1 - 5];
					if(Flag.Is_Go_straight == 1)
					{
						PID_Ahead(&mPID);
					}
				}
				RxFlag1 = 0;
				RxCounter1 = 0;
				RxState = 0;
//				for(i=0;i<10;i++)
//				{
//					RxBuffer1[i]=0x00;      //将存放数据数组清零
//				}
				USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);
			}
			else   //接收错误
			{
				RxState = 0;
				RxCounter1=0;
				for(i=0;i<10;i++)
				{
					RxBuffer1[i]=0x00;      //将存放数据数组清零
				}
			}
		} 
		
		//Receive Corner Flag
		
		else if(RxState==0 && com_data==0xAA)  //0xAA帧头
		{
			RxState=4;
			RxBuffer1[RxCounter1++]=com_data;

		}
		
		else if(RxState==4 && com_data==0xAB)  //0xAB帧头
		{
			RxState=5;
			RxBuffer1[RxCounter1++]=com_data;
		}
		
		else if(RxState==5)
		{
			RxBuffer1[RxCounter1++]=com_data;

			if(RxCounter1 == 4)       //RxBuffer1接受满了,接收数据结束
			{
				RxState=6;
				RxFlag1=1;

//				Corner_Flag = RxBuffer1[RxCounter1 - 5];
			}
		}
		
		else if(RxState==6)		//检测是否接受到结束标志
		{
			RxBuffer1[RxCounter1]=com_data;
			if(RxBuffer1[RxCounter1] == 0x5B)
			{
				USART_ITConfig(USART3,USART_IT_RXNE,DISABLE);//关闭DTSABLE中断
				
				if(RxFlag1)
				{
					Corner_Flag = RxBuffer1[RxCounter1 - 2];
					OLED_ShowString(4, 1, "Turn");
				}
				RxFlag1 = 0;
				RxCounter1 = 0;
				RxState = 0;
//				for(i=0;i<10;i++)
//				{
//					RxBuffer1[i]=0x00;      //将存放数据数组清零
//				}
				USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);
			}
			else   //接收错误
			{
				RxState = 0;
				RxCounter1=0;
				for(i=0;i<10;i++)
				{
					RxBuffer1[i]=0x00;      //将存放数据数组清零
				}
			}
		} 
		
		else   //接收异常
		{
			RxState = 0;
			RxCounter1=0;
			for(i=0;i<10;i++)
			{
				RxBuffer1[i]=0x00;      //将存放数据数组清零
			}
		}
	
	}
		
}

