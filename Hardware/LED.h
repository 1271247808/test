#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"                  // Device header

	void LED_Init(void);
	void LEDG_OFF(void);
	void LEDG_ON(void);
	void LEDR_OFF(void);
	void LEDR_ON(void);
	void LEDSwitch(void);
	
	extern uint8_t LEDG_State;
	extern uint8_t LEDR_State;
#endif
