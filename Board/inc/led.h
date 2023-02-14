#ifndef __LED__
#define __LED__

#include "stm32f10x.h"

/* ����LED���ӵ�GPIO�˿�, �û�ֻ��Ҫ�޸�����Ĵ��뼴�ɸı���Ƶ�LED���� */
// LED1
#define LED1_GPIO_PORT GPIOC               /* GPIO�˿� */
#define LED1_GPIO_CLK RCC_APB2Periph_GPIOC /* GPIO�˿�ʱ�� */
#define LED1_GPIO_PIN GPIO_Pin_13          /* ���ӵ�SCLʱ���ߵ�GPIO */

// LED2
#define LED2_GPIO_PORT GPIOC               /* GPIO�˿� */
#define LED2_GPIO_CLK RCC_APB2Periph_GPIOC /* GPIO�˿�ʱ�� */
#define LED2_GPIO_PIN GPIO_Pin_15          /* ���ӵ�SCLʱ���ߵ�GPIO */

// LED3
#define LED3_GPIO_PORT GPIOC               /* GPIO�˿� */
#define LED3_GPIO_CLK RCC_APB2Periph_GPIOC /* GPIO�˿�ʱ�� */
#define LED3_GPIO_PIN GPIO_Pin_14          /* ���ӵ�SCLʱ���ߵ�GPIO */
//��ö������з�װ

/* ֱ�Ӳ����Ĵ����ķ�������IO */
#define digitalHi(p, i) \
    {                   \
        p->BSRR = i;    \
    } //���Ϊ�ߵ�ƽ
#define digitalLo(p, i) \
    {                   \
        p->BRR = i;     \
    } //����͵�ƽ
#define digitalToggle(p, i) \
    {                       \
        p->ODR ^= i;        \
    } //�����ת״̬

/* �������IO�ĺ� */
#define LED1_TOGGLE digitalToggle(LED1_GPIO_PORT, LED1_GPIO_PIN)
#define LED1_OFF digitalHi(LED1_GPIO_PORT, LED1_GPIO_PIN)
#define LED1_ON digitalLo(LED1_GPIO_PORT, LED1_GPIO_PIN)

#define LED2_TOGGLE digitalToggle(LED2_GPIO_PORT, LED2_GPIO_PIN)
#define LED2_OFF digitalHi(LED2_GPIO_PORT, LED2_GPIO_PIN)
#define LED2_ON digitalLo(LED2_GPIO_PORT, LED2_GPIO_PIN)

#define LED3_TOGGLE digitalToggle(LED3_GPIO_PORT, LED3_GPIO_PIN)
#define LED3_OFF digitalHi(LED3_GPIO_PORT, LED3_GPIO_PIN)
#define LED3_ON digitalLo(LED3_GPIO_PORT, LED3_GPIO_PIN)

typedef enum
{
    LED1,
    LED2,
    LED3,
    LED_ALL
} LED;

extern void LED_GPIO_Init(void);
extern void Led_Set(LED Led, uint8_t State);
extern void WaterFall_Led(void);

#endif /* __LED__ */
