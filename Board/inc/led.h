#ifndef __LED__
#define __LED__

#include "stm32f10x.h"

/* 定义LED连接的GPIO端口, 用户只需要修改下面的代码即可改变控制的LED引脚 */
// LED1
#define LED1_GPIO_PORT GPIOC               /* GPIO端口 */
#define LED1_GPIO_CLK RCC_APB2Periph_GPIOC /* GPIO端口时钟 */
#define LED1_GPIO_PIN GPIO_Pin_13          /* 连接到SCL时钟线的GPIO */

// LED2
#define LED2_GPIO_PORT GPIOC               /* GPIO端口 */
#define LED2_GPIO_CLK RCC_APB2Periph_GPIOC /* GPIO端口时钟 */
#define LED2_GPIO_PIN GPIO_Pin_15          /* 连接到SCL时钟线的GPIO */

// LED3
#define LED3_GPIO_PORT GPIOC               /* GPIO端口 */
#define LED3_GPIO_CLK RCC_APB2Periph_GPIOC /* GPIO端口时钟 */
#define LED3_GPIO_PIN GPIO_Pin_14          /* 连接到SCL时钟线的GPIO */
//用枚举体进行封装

/* 直接操作寄存器的方法控制IO */
#define digitalHi(p, i) \
    {                   \
        p->BSRR = i;    \
    } //输出为高电平
#define digitalLo(p, i) \
    {                   \
        p->BRR = i;     \
    } //输出低电平
#define digitalToggle(p, i) \
    {                       \
        p->ODR ^= i;        \
    } //输出反转状态

/* 定义控制IO的宏 */
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
