#include "main.h"

uint8_t buff_rx[20];
uint16_t buff_pwm[4];
int cont;
char flag_split;

int main(void)	{

	PLL_Init();
//	TIM1_Init();
	
	
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/10);
	
	
	GPIO_Init();
	EXTI_Init();
	USART1_Init();
	Init_PWM();
	
	USART1_String("Carro Velocista...\n");
	
	while(1)	{
			
		if(flag_split == 't')
		{
			uart_split((char*)buff_rx, ",");
			flag_split = 'f';
			
			/*	Motor_setGiro(motor, pwm, sentido de giro)	*/
			Motor_setGiro(1, buff_pwm[0], 1);
			Motor_setGiro(2, buff_pwm[0], 0);
		}
		
	}
}

void GPIO_Init(void)	{

	RCC->AHB1ENR 	|= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOCEN;
	
	/*	LED USER	*/
	GPIOC->MODER |= (1UL<<2*13);
	GPIOC->OSPEEDR |= (3UL<<2*13);
	GPIOC->PUPDR |= (1UL<<2*13);
	
	/*	DRIVER	*/
	
	GPIOA->MODER 		|= ((1UL<<2*3) | (1UL<<2*2) | (1UL<<2*1) | (1UL<<2*0));
	GPIOA->OSPEEDR	|= ((3UL<<2*3) | (3UL<<2*2) | (3UL<<2*1) | (3UL<<2*0));
	GPIOA->PUPDR 		|= ((1UL<<2*3) | (1UL<<2*2) | (1UL<<2*1) | (1UL<<2*0));
	
}

void EXTI_Init(void)	{

	

}

void uart_split(char *buff, const char *c)	{
	
	char *token, letter = 'A'; int x;
	token = strtok(buff, c);
	x = 0;
	
	while	(token != NULL)	{
		buff_pwm[x++] = atoi(token);
		token = strtok(NULL, c);
	}	
}

void Motor_setGiro(uint8_t motor, uint16_t pwm, uint8_t dir)	{

	switch(motor)	{
	
		case 1:
		
			if(dir)	{
			GPIOA->ODR |= (1UL<<0);
			GPIOA->ODR &= ~(1UL<<1);
			} else {
			GPIOA->ODR |= (1UL<<1);
			GPIOA->ODR &= ~(1UL<<0);				
			}
			setTIM4_PWM(motor, pwm);
			break;
		
		case 2:
			
			if(dir)	{
			GPIOA->ODR |= (1UL<<2);
			GPIOA->ODR &= ~(1UL<<3);
			} else {
			GPIOA->ODR |= (1UL<<3);
			GPIOA->ODR &= ~(1UL<<2);				
			}
			setTIM4_PWM(motor, pwm);		
			break;
		
		default:
			GPIOA->ODR &= ~(1UL<<0);
			GPIOA->ODR &= ~(1UL<<1);
			GPIOA->ODR &= ~(1UL<<2);
			GPIOA->ODR &= ~(1UL<<3);
			setTIM4_PWM(1, 0);
			setTIM4_PWM(2, 0);
			break;
	}
}
