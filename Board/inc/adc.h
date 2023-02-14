#ifndef __ADC_H
#define	__ADC_H


#include "stm32f10x.h"

// 注意：用作ADC采集的IO必须没有复用，否则采集电压会有影响
/********************ADC3输入通道（引脚）配置**************************/
#define    ADC_APBxClock_FUN             RCC_APB2PeriphClockCmd
#define    ADC_CLK                       RCC_APB2Periph_ADC1

#define    ADC_GPIO_APBxClock_FUN        RCC_APB2PeriphClockCmd
#define    ADC_GPIO_CLK1                 RCC_APB2Periph_GPIOC  
#define    ADC_PORT1                     GPIOC

#define    ADC_GPIO_APBxClock_FUN2       RCC_APB2PeriphClockCmd
#define    ADC_GPIO_CLK2                 RCC_APB2Periph_GPIOA
#define    ADC_PORT2                     GPIOA



//左中右与 pin 8、6、2对应

// 转换通道个数
#define    NOFCHANEL				     12

#define    ADC_PIN1                      GPIO_Pin_0
#define    ADC_CHANNEL1                  ADC_Channel_0

#define    ADC_PIN2                      GPIO_Pin_1
#define    ADC_CHANNEL2                  ADC_Channel_1

#define    ADC_PIN3                      GPIO_Pin_2
#define    ADC_CHANNEL3                  ADC_Channel_2

#define    ADC_PIN4                      GPIO_Pin_3
#define    ADC_CHANNEL4                  ADC_Channel_3

#define    ADC_PIN5                      GPIO_Pin_4
#define    ADC_CHANNEL5                  ADC_Channel_4

#define    ADC_PIN6                      GPIO_Pin_5
#define    ADC_CHANNEL6                  ADC_Channel_5

#define    ADC_PIN7                      GPIO_Pin_6
#define    ADC_CHANNEL7                  ADC_Channel_6

#define    ADC_PIN8                      GPIO_Pin_7
#define    ADC_CHANNEL8                  ADC_Channel_7

#define    ADC_PIN9                      GPIO_Pin_0
#define    ADC_CHANNEL9                  ADC_Channel_10

#define    ADC_PIN10                      GPIO_Pin_1
#define    ADC_CHANNEL10                  ADC_Channel_11

#define    ADC_PIN11                      GPIO_Pin_2
#define    ADC_CHANNEL11                  ADC_Channel_12

#define    ADC_PIN12                      GPIO_Pin_3
#define    ADC_CHANNEL12                  ADC_Channel_13


// ADC1 对应 DMA1通道1，ADC3对应DMA2通道5，ADC2没有DMA功能
#define    ADC_x                         ADC1
#define    ADC_DMA_CHANNEL               DMA1_Channel1
#define    ADC_DMA_CLK                   RCC_AHBPeriph_DMA1

extern void ADCx_Init(void);

#endif /* __ADC_H */
