#include "PLL.h"

#define ENABLE_IRQ_TIM1	1

/*
	Bits 12:10 PPRE1: APB Low speed prescaler (APB1)
			0xx: AHB clock not divided
			100: AHB clock divided by 2 <!>
			101: AHB clock divided by 4
			110: AHB clock divided by 8
			111: AHB clock divided by 16
*/

volatile uint32_t us_ticks;

void PLL_Init(void)
{
	RCC->CR |= RCC_CR_HSEON;
	while(!(RCC->CR & RCC_CR_HSERDY));
	
//	RCC->CFGR |= RCC_CFGR_SW_HSE;
	
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;
	RCC->CFGR |= (0x4 << RCC_CFGR_PPRE1_Pos); // max 50MHz
//	RCC->CFGR |= (0x4 << RCC_CFGR_PPRE2_Pos); // max 100MHz
	RCC->CFGR &=~RCC_CFGR_PPRE2_Msk; // max 100MHz

	RCC->PLLCFGR = 0;
//	RCC->PLLCFGR |= 0x3219; // 100 MHz
//	RCC->PLLCFGR |= 0x3019; // 96 MHz
	RCC->PLLCFGR |= 0x2019; // 64 MHz

	RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC;
	
	FLASH->ACR |= 0x3 << FLASH_ACR_LATENCY_Pos;
	PWR->CR |= 0x3<<PWR_CR_VOS_Pos;
	RCC->CR |= RCC_CR_PLLON;
	while(!(RCC->CR & RCC_CR_PLLRDY));

	RCC->CFGR |= RCC_CFGR_SW_PLL;

	SystemCoreClockUpdate();
}

void TIM1_Init(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	
	TIM1->CR1 &=~ TIM_CR1_CEN;
	

	TIM1->PSC = (SystemCoreClock/SystemCoreClock) - 1;
	TIM1->ARR = 100;	
	
	#if ENABLE_IRQ_TIM1
		TIM1->DIER |= TIM_DIER_UIE;
		NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);
	#endif
	
	TIM1->CR1 |= TIM_CR1_CEN;
}

__INLINE uint32_t micros(void)
{
		return us_ticks;
}

void TIM1_UP_TIM10_IRQHandler(void) {

	TIM1->SR &= ~TIM_SR_UIF;	
	us_ticks++;
}
