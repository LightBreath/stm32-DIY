#include "stm32f10x.h"
#include "include.h"
#include "exti.h"

/**
  * @brief        按键中断的 GPIO 初始化函数
  * @param        无
  * @retval       无
  * @author       718 Lab
***/
static void Key_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(KEY1_GPIO_CLK, ENABLE);
    RCC_APB2PeriphClockCmd(KEY2_GPIO_CLK, ENABLE);

    GPIO_InitStructure.GPIO_Pin = KEY1_GPIO_PIN;         // KEY1
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = KEY2_GPIO_PIN;         // KEY2
    GPIO_Init(KEY2_GPIO_PORT, &GPIO_InitStructure);
}

/**
  * @brief        按键外部中断 EXTI 配置函数
  * @param        无
  * @retval       无
  * @author       718 Lab
***/
static void Key_EXIT_Init(void)
{
    EXTI_InitTypeDef EXIT_InitStruct;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); // 打开AFIO的端口时钟（EXTI线的时钟）

    //GPIOG9	  中断线以及中断初始化配置 下降沿触发       // KEY1
    GPIO_EXTILineConfig(KEY1_EXTI_PORT, KEY1_EXTI_PIN);  // 选择中断线
    EXIT_InitStruct.EXTI_Line = KEY1_EXTI_LINE;          // 使能中断线
    EXIT_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;     // 产生中断（而不是事件）
    EXIT_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling; // 下降沿触发
    EXIT_InitStruct.EXTI_LineCmd = ENABLE;               // 使能中断
    EXTI_Init(&EXIT_InitStruct);                         // 根据 EXTI_InitStruct 中指定的参数初始化外设 EXTI 寄存器

    //GPIOD7	  中断线以及中断初始化配置 下降沿触发       // KEY2
    GPIO_EXTILineConfig(KEY2_EXTI_PORT, KEY2_EXTI_PIN);  // 选择中断线
    EXIT_InitStruct.EXTI_Line = KEY2_EXTI_LINE;          // 使能中断线
    EXTI_Init(&EXIT_InitStruct);                         // 根据 EXTI_InitStruct 中指定的参数初始化外设 EXTI 寄存器
}

/**
  * @brief        按键中断 NVIC 配置函数
  * @param        无
  * @retval       无
  * @author       718 Lab
***/
static void Key_NVIC_Init(void)
{
    NVIC_InitTypeDef NVIC_InitStruct;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);           // 设置 NVIC 中断分组 2:2 位抢占优先级，2 位响应优先级
    NVIC_InitStruct.NVIC_IRQChannel = EXTI9_5_IRQn;           // 选择 EXTI_Line19、7 所在的外部中断通道（5——9公用一个通道）
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x02; // 通道的抢占优先级 2
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x01;        // 通道的子优先级 1
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;              // 使能外部中断通道
    NVIC_Init(&NVIC_InitStruct);                              // 根据 NVIC_InitStruct 中指定的参数初始化外设 NVIC 寄存器
}

/**
  * @brief        按键中断初始化函数
  * @param        无
  * @retval       无
  * @author       718 Lab
***/
void GPIO_EXIT_Init(void)
{
    Key_GPIO_Init();
    Key_EXIT_Init();
    Key_NVIC_Init();
}

/**
  * @brief        按键中断的中断服务函数
  * @param        无
  * @retval       无
  * @note         它的实际名称是EXTI15_10_IRQHandler, 是15到10通道对应的中断服务程序, 底层已经将通道和程序指向好
  * @author       718 Lab
***/
void KEY_IRQHandle1(void)
{

    if (EXTI_GetFlagStatus(KEY1_EXTI_LINE))
    {
        if (KEY1 == 0)
        {
            LED1_TOGGLE;
            Usart_SendString(USARTx, "gotta111\n");
        }
        EXTI_ClearITPendingBit(KEY1_EXTI_LINE);
    }

    if (EXTI_GetFlagStatus(KEY2_EXTI_LINE))
    {
        if (KEY2 == 0)
        {
            LED2_TOGGLE;
            Usart_SendString(USARTx, "wanna222\n");
        }
        EXTI_ClearITPendingBit(KEY2_EXTI_LINE);
    }
}
