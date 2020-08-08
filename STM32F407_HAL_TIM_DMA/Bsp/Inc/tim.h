#ifndef __TIM_H
#define __TIM_H

#include "stm32f4xx.h"

extern TIM_HandleTypeDef htim3;

void HAL_TIM_MspPostInit(TIM_HandleTypeDef* timHandle);
void tim3_init(void);

#endif /* __TIM_H */

