#include "Interrupt.h"

extern uint8_t buff_rx[20];
extern int cont;
extern char flag_split;
static volatile uint8_t rx_usart1;
static char ch;
int x;


void SysTick_Handler(void)	{
	
	GPIOC->ODR ^= 1UL<<13;

}

void EXTI9_5_IRQHandler(void)	{

	EXTI->PR |= EXTI_PR_PR5;


}

void sep(uint8_t c)	{

	static char letter;
	
	

}

void USART1_IRQHandler(void)	{

	rx_usart1 = USART1->DR ;
	if(rx_usart1== '*')	{
	
		buff_rx[cont] = USART1->DR;
		cont = 0;
		flag_split = 't';
		
	} else	{
		buff_rx[cont] = USART1->DR;
		cont++;
	}

}
