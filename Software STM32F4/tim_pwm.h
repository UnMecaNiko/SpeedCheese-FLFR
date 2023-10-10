#ifndef TIM_PWM_H_
#define TIM_PWM_H_

#include "stm32f4xx.h"
#include <stdio.h>
#include <stdint.h>

#define PWM_LOW 	(uint32_t)100
#define PWM_HIGH	(uint32_t)16600

#ifdef __cplusplus
extern "C"	{
#endif

void setTIM4_PWM(uint8_t ch, uint32_t pwm);
void Init_PWM(void);


#ifdef __cplusplus
	}
#endif

#endif
