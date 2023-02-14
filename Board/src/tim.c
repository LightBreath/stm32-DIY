#include "tim.h"
#include "led.h"

__IO uint64_t time; //ʹ�� volatile ����,��ֹ�������Ż�
/*
 * ע�⣺TIM_TimeBaseInitTypeDef�ṹ��������5����Ա��TIM6��TIM7�ļĴ�������ֻ��
 * TIM_Prescaler��TIM_Period������ʹ��TIM6��TIM7��ʱ��ֻ���ʼ����������Ա����
 * ����������Ա��ͨ�ö�ʱ���͸߼���ʱ�����е�.
 *-----------------------------------------------------------------------------
 *typedef struct
 *{ TIM_Prescaler            ����
 *	TIM_CounterMode			 TIMx,x[6,7]û�У���������
 *  TIM_Period               ����
 *  TIM_ClockDivision        TIMx,x[6,7]û�У���������
 *  TIM_RepetitionCounter    TIMx,x[1,8,15,16,17]����
 *}TIM_TimeBaseInitTypeDef;
 *-----------------------------------------------------------------------------
 */

/**
 * @brief        ��ʱ���жϳ�ʼ��
 * @param        arr �Զ���װ�ؼĴ�����ֵ
 * @param        psc ʱ��Ԥ��Ƶ��
 * @retval       ��
 * @note         ������Ƶ��Ϊ freq = 72M/(psc+1) , ÿ�� (arr+1)/freq �����һ�ζ�ʱ���ж�
 * @author       718 Lab
*/
void TIM_Init(uint16_t arr, uint16_t psc)
{
    // ��ʱ��TIM��ʼ��
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_APBxClock_FUN(TIM_CLK, ENABLE);                         // ������ʱ��ʱ��, ���ڲ�ʱ�� CK_INT=72M
    TIM_TimeBaseStructure.TIM_Period = arr;                     // �Զ���װ�ؼĴ�����ֵ���ۼ� TIM_Period + 1 ��Ƶ�ʺ����һ�����»����ж�
    TIM_TimeBaseStructure.TIM_Prescaler = psc;                  // ����ʱ��Ԥ��Ƶ��
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     // ʱ�ӷ�Ƶ���ӣ�����������������õõ���
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // ����������ģʽ��ѡ�����ϼ���
    TIM_TimeBaseInit(TIM, &TIM_TimeBaseStructure);              // ��ʼ����ʱ��
    TIM_ClearFlag(TIM, TIM_FLAG_Update);                        // ����������жϱ�־λ
    TIM_ITConfig(TIM, TIM_IT_Update, ENABLE);                   // ʹ�ܶ�ʱ���ж�,��������ж�
    TIM_Cmd(TIM, ENABLE);                                       // ʹ�ܼ�����

    // �ж����ȼ�NVIC����
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);           // ���� NVIC �жϷ��� 2:2 λ��ռ���ȼ�, 2 λ��Ӧ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannel = TIM_IRQ;             // �����ж���Դ
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; // ���������ȼ�Ϊ 0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;        // ������ռ���ȼ�Ϊ3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           // IRQ ͨ����ʹ��
    NVIC_Init(&NVIC_InitStructure);                           // ��ʼ�� NVIC �Ĵ���
}

/**
 * @brief        ��ʱ���жϷ�����
 * @param        ��
 * @retval       ��
 * @author       718 Lab
*/
void TIM_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM, TIM_IT_Update)) // ��� TIM3 �����жϷ������
    {
        LED1_TOGGLE;
        TIM_ClearITPendingBit(TIM, TIM_IT_Update); // ��� TIMx �����жϱ�־
    }
    
}

/*********************************************END OF FILE**********************/
