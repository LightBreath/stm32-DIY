#include "stm32f10x.h"
#include "include.h"
#include "exti.h"

/**
  * @brief        �����жϵ� GPIO ��ʼ������
  * @param        ��
  * @retval       ��
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
  * @brief        �����ⲿ�ж� EXTI ���ú���
  * @param        ��
  * @retval       ��
  * @author       718 Lab
***/
static void Key_EXIT_Init(void)
{
    EXTI_InitTypeDef EXIT_InitStruct;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); // ��AFIO�Ķ˿�ʱ�ӣ�EXTI�ߵ�ʱ�ӣ�

    //GPIOG9	  �ж����Լ��жϳ�ʼ������ �½��ش���       // KEY1
    GPIO_EXTILineConfig(KEY1_EXTI_PORT, KEY1_EXTI_PIN);  // ѡ���ж���
    EXIT_InitStruct.EXTI_Line = KEY1_EXTI_LINE;          // ʹ���ж���
    EXIT_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;     // �����жϣ��������¼���
    EXIT_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling; // �½��ش���
    EXIT_InitStruct.EXTI_LineCmd = ENABLE;               // ʹ���ж�
    EXTI_Init(&EXIT_InitStruct);                         // ���� EXTI_InitStruct ��ָ���Ĳ�����ʼ������ EXTI �Ĵ���

    //GPIOD7	  �ж����Լ��жϳ�ʼ������ �½��ش���       // KEY2
    GPIO_EXTILineConfig(KEY2_EXTI_PORT, KEY2_EXTI_PIN);  // ѡ���ж���
    EXIT_InitStruct.EXTI_Line = KEY2_EXTI_LINE;          // ʹ���ж���
    EXTI_Init(&EXIT_InitStruct);                         // ���� EXTI_InitStruct ��ָ���Ĳ�����ʼ������ EXTI �Ĵ���
}

/**
  * @brief        �����ж� NVIC ���ú���
  * @param        ��
  * @retval       ��
  * @author       718 Lab
***/
static void Key_NVIC_Init(void)
{
    NVIC_InitTypeDef NVIC_InitStruct;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);           // ���� NVIC �жϷ��� 2:2 λ��ռ���ȼ���2 λ��Ӧ���ȼ�
    NVIC_InitStruct.NVIC_IRQChannel = EXTI9_5_IRQn;           // ѡ�� EXTI_Line19��7 ���ڵ��ⲿ�ж�ͨ����5����9����һ��ͨ����
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x02; // ͨ������ռ���ȼ� 2
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x01;        // ͨ���������ȼ� 1
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;              // ʹ���ⲿ�ж�ͨ��
    NVIC_Init(&NVIC_InitStruct);                              // ���� NVIC_InitStruct ��ָ���Ĳ�����ʼ������ NVIC �Ĵ���
}

/**
  * @brief        �����жϳ�ʼ������
  * @param        ��
  * @retval       ��
  * @author       718 Lab
***/
void GPIO_EXIT_Init(void)
{
    Key_GPIO_Init();
    Key_EXIT_Init();
    Key_NVIC_Init();
}

/**
  * @brief        �����жϵ��жϷ�����
  * @param        ��
  * @retval       ��
  * @note         ����ʵ��������EXTI15_10_IRQHandler, ��15��10ͨ����Ӧ���жϷ������, �ײ��Ѿ���ͨ���ͳ���ָ���
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
