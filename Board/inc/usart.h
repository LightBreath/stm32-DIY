#ifndef __USART_H__
#define __USART_H__

#include "stm32f10x.h"
#include <stdio.h>

// 串口宏定义，不同的串口挂载的总线不一样，移植时需要修改这几个宏
#define USARTx                     UART4
#define USART_CLK                  RCC_APB1Periph_UART4
#define USART_APBxClkCmd           RCC_APB1PeriphClockCmd
#define USART_BAUDRATE             9600

// USART GPIO 引脚宏定义
#define USART_GPIO_CLK             (RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD)
#define USART_GPIO_APBxClkCmd      RCC_APB2PeriphClockCmd

#define USART_TX_GPIO_PORT         GPIOC
#define USART_TX_GPIO_PIN          GPIO_Pin_10
#define USART_RX_GPIO_PORT         GPIOC
#define USART_RX_GPIO_PIN          GPIO_Pin_11

#define USART_IRQ                  UART4_IRQn
#define USART_IRQHandler           UART4_IRQHandler

#define		Middle_light ADC_ConvertedValueLocal[11]	// 中间对管
#define		Left_light   ADC_ConvertedValueLocal[1]	// 左对管
#define		Right_light  ADC_ConvertedValueLocal[7]    //右对管
#define	  Rightstring  ADC_ConvertedValueLocal[5] //最右侧对管
#define	  Leftstring  ADC_ConvertedValueLocal[9]  //最左侧对管
#define   Block       ADC_ConvertedValueLocal[3]    



extern void USART_Config(void);
extern void Test_ADC_PRINTF(void);
extern void Usart_SendByte(USART_TypeDef *pUSARTx, uint8_t ch);
extern void Usart_SendString(USART_TypeDef *pUSARTx, char *str);
extern void Usart_SendHalfWord(USART_TypeDef *pUSARTx, uint16_t ch);
void Stright_on (int speed,int time);
void Stright_down (int speed,int time);
void Turn_left (void);
void Turn_right (void);
void emg_stop(void);
void Microleft(void);
void Microright(void);
#endif /* __USART_H__ */
