#include "tim_pwm.h"

static void TIM4_GPIO_Init(void);

void setTIM4_PWM(uint8_t ch, uint32_t pwm)	{

	uint32_t duty = (pwm > PWM_HIGH) ? (pwm > PWM_HIGH ? PWM_HIGH : pwm ) : (pwm < PWM_LOW ? PWM_LOW : pwm );
	
	switch(ch)	{
	
		case 1:
			TIM4->CCR1 = duty;
			break;
		case 2:
			TIM4->CCR2 = duty;
			break;
			
		default:
			TIM4->CCR1 = duty;
			TIM4->CCR2 = duty;
			break;
	}
}

void Init_PWM(void)	{
	
	TIM4_GPIO_Init();
	
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	
	TIM4->CR1 &= ~TIM_CR1_CEN;
	
	TIM4->PSC = (SystemCoreClock/1000000) - 1;
//	TIM4->ARR = (uint32_t)20000-1; // 50 Hz
	TIM4->ARR = (uint32_t)16666-1; // 60 Hz

	
	TIM4->CCMR1 &= ~(TIM_CCMR1_CC2S_Msk | TIM_CCMR1_CC1S_Msk);
	
	TIM4->CCMR1 |= (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 |
									TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1);
	
	TIM4->CCER |= (TIM_CCER_CC2E | TIM_CCER_CC1E);
	
	TIM4->CCR1 = PWM_LOW;
	TIM4->CCR2 = PWM_LOW;
	
	TIM4->CR1 |= TIM_CR1_CEN;
	
}

static void TIM4_GPIO_Init(void)	{

	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	
	GPIOB->MODER 		&= 	~(GPIO_MODER_MODE7_Msk | GPIO_MODER_MODE6_Msk);
	
	GPIOB->MODER 		|= 	GPIO_MODER_MODE7_1 | GPIO_MODER_MODE6_1;
	
	GPIOB->OSPEEDR 	|= 	GPIO_OSPEEDR_OSPEED7_Msk | GPIO_OSPEEDR_OSPEED6_Msk;
	
	GPIOB->PUPDR	&= ~(GPIO_PUPDR_PUPD7_Msk | GPIO_PUPDR_PUPD6_Msk);
	
	GPIOB->AFR[0] |= (0x2 << GPIO_AFRL_AFSEL7_Pos | 0x2 << GPIO_AFRL_AFSEL6_Pos);

}
