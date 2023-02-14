#ifndef __BSP_TIMEBASE_H
#define __BSP_TIMEBASE_H

#include "stm32f10x.h"

#define TIM                                 TIM3
#define TIM_APBxClock_FUN                   RCC_APB1PeriphClockCmd
#define TIM_CLK                             RCC_APB1Periph_TIM3
// #define            TIM_Period            100000 - 1
// #define            TIM_Prescaler         72 - 1
#define TIM_IRQ                             TIM3_IRQn
#define TIM_IRQHandler                      TIM3_IRQHandler

extern __IO uint64_t time;

extern void TIM_Init(uint16_t arr, uint16_t psc);

#endif /* __BSP_TIMEBASE_H */
