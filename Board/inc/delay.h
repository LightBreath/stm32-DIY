#ifndef __DELAY_H
#define __DELAY_H
#include "stm32f10x.h"  

extern void Delay_Init(void);
extern void Delay_MS(u16 nms);
extern void Delay_US(u32 nus);

#endif
