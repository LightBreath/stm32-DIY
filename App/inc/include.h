#ifndef __INCLUDE__
#define __INCLUDE__

#include "delay.h"
#include "led.h"
#include "exti.h"
#include "usart.h"
#include "tim.h"
#include "oled.h"
#include "adc.h"
#include "servo.h"
#include "motor.h"

extern __IO uint16_t ADC_ConvertedValue[NOFCHANEL];
extern float ADC_ConvertedValueLocal[NOFCHANEL]; 

#endif


