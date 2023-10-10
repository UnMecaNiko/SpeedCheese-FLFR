#ifndef PLL_H_
#define PLL_H_

#include "stm32f4xx.h"

#define PLL_Q	4
#define PLL_P	2
#define PLL_N	100
#define PLL_M	8

#ifdef __cplusplus
extern "C" {
#endif

typedef struct	{
	
	__IO uint32_t SW0				:		1;
	__IO uint32_t SW1				:		1;
	__IO uint32_t SWS0			:		1;
	__IO uint32_t SWS1			:		1;
	__IO uint32_t HPRE			:		4;
	__IO uint32_t RESERVED	:		2;
	__IO uint32_t PRE1			:		3;
	__IO uint32_t PRE2			:		3;
	__IO uint32_t RTCPRE		:		5;
	__IO uint32_t MCO1			:		2;
	__IO uint32_t I2SSCR		:		1;
	__IO uint32_t MCO1_PRE	:		3;
	__IO uint32_t MCO2_PRE	:		3;
	__IO uint32_t MCO2			:		2;
	
}	RCC_CFGR_t;

void PLL_Init(void);
void TIM1_Init(void);
void TIM1_UP_TIM10_IRQHandler(void);

uint32_t micros(void);


#ifdef __cplusplus
}
#endif
#endif
