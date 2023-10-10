#include "UART_STM32F411.h"
#include <string.h>

static void GPIO_UART_Init(void);

void USART1_Init(void)
{
	
	GPIO_UART_Init();
	SystemCoreClockUpdate();
	
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

	/* Configuracion USARTx*/
	
	USART1->CR1 &=~ USART_CR1_M;  // 8 Data Bit
	USART1->CR1 |= (USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE);
	
	USART1->BRR = 0;
//	USART1->BRR = (0x4 << USART_BRR_DIV_Fraction_Pos) | (0x36 << USART_BRR_DIV_Mantissa_Pos); // PLL=100 MHz,115200
	
		USART1->BRR = (0x2E << USART_BRR_DIV_Fraction_Pos) | (0x23 << USART_BRR_DIV_Mantissa_Pos); // PLL=64 MHz,115200
//	USART1->BRR = 0x1B2; // PLL=100MHz/2,115200
	
	NVIC_EnableIRQ(USART1_IRQn);
	USART1->CR1 |= USART_CR1_UE;	

	
}

void USART1_String(char* str)
{
	while(*str)
	{
		while(!(USART1->SR & USART_SR_TXE));
		USART1->DR = (uint8_t)*str++;
	}
}

/*	PA9		TX1	
		PA10	RX1	*/
static void GPIO_UART_Init(void)
{

	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	
	GPIOA->MODER &= ~((3UL<<2*9) | (3UL<<2*10));
	
	GPIOA->MODER   |= ((2UL<<2*9) | (2UL<<2*10));
	GPIOA->OSPEEDR |= ((3UL<<2*9) | (3UL<<2*10));
	
	GPIOA->AFR[1] |= (0x7 << 4U);
	GPIOA->AFR[1] |= (0x7 << 8U);
	
}
