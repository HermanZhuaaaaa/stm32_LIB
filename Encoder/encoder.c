#include "stm32f4xx.h"                  // Device header
#include "tim.h"

static short Encoder_GetCount(void)
{
	short counter = __HAL_TIM_GET_COUNTER(&htim3);
	__HAL_TIM_SetCounter(&htim3,0);
	return counter;
}

float Encoder_GetCircle(void)
{
	float ff = Encoder_GetCount()/11.0/19.0/4.0;
	return ff;
}
