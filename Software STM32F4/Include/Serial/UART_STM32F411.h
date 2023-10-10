#ifndef UART_STM32F411_H_
#define UART_STM32F411_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f4xx.h"


void USART1_Init(void);
void USART1_String(char* str);


#ifdef __cplusplus
}
#endif
#endif
