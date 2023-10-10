#ifndef MAIN_H_
#define MAIN_H_

#include "stm32f4xx.h"
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include "UART_STM32F411.h"
#include "PLL.h"
#include "tim_pwm.h"

#include "QTR_8RC.h"

#ifdef __cplusplus
extern	"C"	{
#endif

void GPIO_Init(void);
void EXTI_Init(void);
void uart_split(char *buff, const char *c);

void Motor_setGiro(uint8_t motor, uint16_t pwm, uint8_t dir);

#ifdef __cplusplus
}
#endif
#endif
