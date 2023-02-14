#ifndef _EXIT_H_
#define _EXIT_H_

#define KEY_IRQHandle1  EXTI9_5_IRQHandler // KEY

//KEY defination
// KEY1
#define KEY1_GPIO_PORT  GPIOC                /* GPIO �˿� */
#define KEY1_GPIO_CLK   RCC_APB2Periph_GPIOC /* GPIO �˿�ʱ�� */
#define KEY1_GPIO_PIN   GPIO_Pin_9           /* ���ӵ� SCL ʱ���ߵ� GPIO */

// KEY2
#define KEY2_GPIO_PORT  GPIOC                /* GPIO �˿� */
#define KEY2_GPIO_CLK   RCC_APB2Periph_GPIOC /* GPIO �˿�ʱ�� */
#define KEY2_GPIO_PIN   GPIO_Pin_8           /* ���ӵ�SCLʱ���ߵ� GPIO */

// KEY1 EXTI
#define KEY1_EXTI_PORT  GPIO_PortSourceGPIOC
#define KEY1_EXTI_PIN   GPIO_PinSource8
#define KEY1_EXTI_LINE  EXTI_Line9

// KEY2 EXTI
#define KEY2_EXTI_PORT  GPIO_PortSourceGPIOC
#define KEY2_EXTI_PIN   GPIO_PinSource9
#define KEY2_EXTI_LINE  EXTI_Line8

#define KEY1 GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_9) // ��ȡKEY1
#define KEY2 GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_8) // ��ȡKEY2

extern void GPIO_EXIT_Init(void);
extern void Key_GPIO_Initg(void);
extern void Key_EXIT_Init(void);
extern void Key_NVIC_Init(void);
#endif
