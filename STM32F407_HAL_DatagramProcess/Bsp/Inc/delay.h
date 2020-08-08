#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f4xx.h"
#include "dwt.h"


#define DWT_DELAY_DISABLED  //不使用DWT延时函数

static inline void delay(uint32_t) __attribute__((always_inline, unused));
static inline void delay(uint32_t ms)
{
    HAL_Delay(ms);
}

static inline void delayMicroseconds(uint32_t) __attribute__((always_inline, unused));
static inline void delayMicroseconds(uint32_t us)
{
#if defined(DWT_BASE) && !defined(DWT_DELAY_DISABLED)
  int32_t start  = dwt_getCycles();
  int32_t cycles = us * (SystemCoreClock / 1000000);

  while ((int32_t)dwt_getCycles() - start < cycles);
#else
    __IO uint32_t currentTicks = SysTick->VAL;
  /* Number of ticks per millisecond */
  const uint32_t tickPerMs = SysTick->LOAD + 1;
  /* Number of ticks to count */
  const uint32_t nbTicks = ((us - ((us > 0) ? 1 : 0)) * tickPerMs) / 1000;
  /* Number of elapsed ticks */
  uint32_t elapsedTicks = 0;
  __IO uint32_t oldTicks = currentTicks;
  do {
    currentTicks = SysTick->VAL;
    elapsedTicks += (oldTicks < currentTicks) ? tickPerMs + oldTicks - currentTicks :
                    oldTicks - currentTicks;
    oldTicks = currentTicks;
  } while (nbTicks > elapsedTicks);
#endif
}

void delay_init(void);

#endif /* __DELAY_H */
