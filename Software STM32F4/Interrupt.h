#ifndef Interrupt_H_
#define Interrupt_H_

#include "main.h"	

#ifdef __cplusplus
extern	"C"	{
#endif


void SysTick_Handler(void);
void EXTI9_5_IRQHandler(void);
void USART1_IRQHandler(void);


#ifdef __cplusplus
}
#endif

#endif 
