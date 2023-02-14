#include "led.h"
#include "include.h"

/**
  * @brief        与 LED 灯对应的 GPIO 端口初始化函数
  * @param        无
  * @retval       无
  * @author       718 Lab
***/
void LED_GPIO_Init(void)
{
    /* 定义一个 GPIO_InitTypeDef 类型的结构体 */
    GPIO_InitTypeDef GPIO_InitStructure;

    /* 开启 LED 相关的 GPIO 外设时钟 */
    RCC_APB2PeriphClockCmd(LED1_GPIO_CLK | LED2_GPIO_CLK | LED3_GPIO_CLK, ENABLE);
    /* 选择要控制的 GPIO 引脚 */
    GPIO_InitStructure.GPIO_Pin = LED1_GPIO_PIN;
    /* 设置引脚模式为通用推挽输出 */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    /* 设置引脚速率为 50MHz */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    /* 调用库函数，初始化 GPIO */
    GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStructure);

    /* 选择要控制的GPIO引脚 */
    GPIO_InitStructure.GPIO_Pin = LED2_GPIO_PIN;
    /* 初始化GPIO */
    GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStructure);

    /* 选择要控制的 GPIO 引脚 */
    GPIO_InitStructure.GPIO_Pin = LED3_GPIO_PIN;
    /* 调用库函数，初始化 GPIOF */
    GPIO_Init(LED3_GPIO_PORT, &GPIO_InitStructure);
}

/**
  * @brief        控制 LED 对应的 GPIO 引脚的状态
  * @param        led   需要控制的 LED (LED1/LED2/LED3/LED_ALL)
  * @param        State 需要设置的状态(0 为低电平 1 为高电平)
  * @retval       无
  * @author       718 Lab
***/
void Led_Set(LED Led, uint8_t State)
{
    if (Led == LED1)
    {
        if (State == 1)
            GPIO_ResetBits(LED1_GPIO_PORT, LED1_GPIO_PIN);
        else if (State == 0)
            GPIO_SetBits(LED1_GPIO_PORT, LED1_GPIO_PIN);
    }
    if (Led == LED2)
    {
        if (State == 1)
            GPIO_ResetBits(LED2_GPIO_PORT, LED2_GPIO_PIN);
        else if (State == 0)
            GPIO_SetBits(LED2_GPIO_PORT, LED2_GPIO_PIN);
    }
    if (Led == LED3)
    {
        if (State == 1)
            GPIO_ResetBits(LED3_GPIO_PORT, LED3_GPIO_PIN);
        else if (State == 0)
            GPIO_SetBits(LED3_GPIO_PORT, LED3_GPIO_PIN);
    }
    else if (Led == LED_ALL)
    {
        if (State == 1)
        {
            GPIO_ResetBits(GPIOC, LED1_GPIO_PIN | LED2_GPIO_PIN | LED3_GPIO_PIN);
        }
        else if (State == 0)
        {
            GPIO_SetBits(GPIOC, LED1_GPIO_PIN | LED2_GPIO_PIN | LED3_GPIO_PIN);
        }
    }
}

/**
  * @brief        控制 LED 实现流水灯
  * @param        无
  * @retval       无
  * @note         具体流水功能视现象而定, 可能可以改进
  * @author       718 Lab
***/
void WaterFall_Led(void)
{
    while (1)
    {
        Led_Set(LED_ALL, 0);
        Led_Set(LED1, 1);
        Delay_MS(150);
        Led_Set(LED1, 0);
        Led_Set(LED2, 1);
        Delay_MS(150);
        Led_Set(LED2, 0);
        Led_Set(LED3, 1);
        Delay_MS(150);
        Led_Set(LED3, 0);
        Led_Set(LED2, 1);
        Delay_MS(150);
        Led_Set(LED1, 0);
        Led_Set(LED2, 1);
        Delay_MS(150);
        Led_Set(LED1, 0);
        Led_Set(LED3, 1);
        Delay_MS(150);
        Led_Set(LED2, 0);
    }
}
