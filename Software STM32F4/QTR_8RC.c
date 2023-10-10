#include "QTR_8RC.h"

int sensor_read = 0x00000000;
int last_end = 0;

static void GPIO_Init(void);
static GPIO_PinState GPIO_Read(GPIO_TypeDef *gpio, uint16_t GPIO_Pin);


int QTR8RC_read(void)	{
	
	sensor_read = 0x00000000;
	int pos = 0;
  int active = 0;
	
	if (GPIO_Read(QTR_GPIO_Port, SENSOR1_Pin)) {
		sensor_read |= 0x00000001;
		pos += 1000;
    active++;
		last_end = 1;
	}
	if (GPIO_Read(QTR_GPIO_Port, SENSOR2_Pin)) {
		sensor_read |= 0x00000010;
		pos += 2000;
    active++;
  }
	if (GPIO_Read(QTR_GPIO_Port, SENSOR3_Pin)) {
		sensor_read |= 0x00000100;
		pos += 3000;
    active++;
  }
	if (GPIO_Read(QTR_GPIO_Port, SENSOR4_Pin)) {
		sensor_read |= 0x00001000;
		pos += 4000;
    active++;
  }
	if (GPIO_Read(QTR_GPIO_Port, SENSOR5_Pin)) {
		sensor_read |= 0x00010000;
		pos += 5000;
    active++;
  }
	if (GPIO_Read(QTR_GPIO_Port, SENSOR6_Pin)) {
		sensor_read |= 0x00100000;
		pos += 6000;
    active++;
  }
	if (GPIO_Read(QTR_GPIO_Port, SENSOR7_Pin)) {
		sensor_read |= 0x01000000;
		pos += 7000;
    active++;
  }
	if (GPIO_Read(QTR_GPIO_Port, SENSOR8_Pin)) {
		sensor_read |= 0x10000000;
		pos += 8000;
    active++;
		last_end = 0;
  }	
	
	return pos/active;
}


static GPIO_PinState GPIO_Read(GPIO_TypeDef *gpio, uint16_t GPIO_Pin)	{

	GPIO_PinState bitstatus;

  if ((gpio->IDR & GPIO_Pin) != (uint32_t)GPIO_PIN_RESET)
  {
    bitstatus = GPIO_PIN_SET;
  }
  else
  {
    bitstatus = GPIO_PIN_RESET;
  }
	
  return bitstatus;
}
