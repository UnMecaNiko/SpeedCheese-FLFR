#ifndef QTR_8RC_H_
#define QTR_8RC_H_

#include "stm32f4xx.h"

#define SENSOR1_Pin 0
#define SENSOR2_Pin 1
#define SENSOR3_Pin 2
#define SENSOR4_Pin 3
#define SENSOR5_Pin 4
#define SENSOR6_Pin 5
#define SENSOR7_Pin 6
#define SENSOR8_Pin 7

#define QTR_GPIO_Port GPIOA

#ifdef __cplusplus
extern "C"	{
#endif

typedef enum
{
  GPIO_PIN_RESET = 0u,
  GPIO_PIN_SET
} GPIO_PinState;

int QTR8RC_read(void);

#ifdef __cplusplus
	}
#endif
#endif
