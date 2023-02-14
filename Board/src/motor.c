#include "motor.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"


/**
  * @brief	      �����ʼ������
  * @param        ��
  * @retval       ��
  * @author       718 Lab
  */
void TIM_MOTOR_Init(void)
{
    /* --------------����Ƚ�ͨ��1��2��3��4��GPIO��ʼ��------------- */
    GPIO_InitTypeDef GPIO_InitStructure; //����GPIO��ʼ���ṹ��

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);                             //ʹ��AFIO����ʱ��	//ʹ����ӳ��IOʱ��
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);                         //shut JTAG
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_1 | GPIO_Pin_0; //����GPIO�ܽ�
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                                  //�����������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                                //�������Ƶ��
    GPIO_Init(GPIOB, &GPIO_InitStructure);                                           //��ʼ��GPIO

    /*----------------------ʱ���ṹ���ʼ��-----------------------*/
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; //������ʱ��ʱ���ṹ��

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʹ����ӳ�䶨ʱ��ʱ��

    /* �������ڣ���������Ϊ0.0005s����ʾ��Tout= ((arr+1)*(psc+1))/Tclk */
    TIM_TimeBaseStructure.TIM_Period = 20000 - 1;                 //��ʱ������arr�����Զ���װ�ؼĴ�����ֵ
                                                                //�ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
    TIM_TimeBaseStructure.TIM_Prescaler = 71;                   //��ʱ��Ԥ��Ƶ������psc��ʱ��Դ����Ԥ��Ƶ�����Ƕ�ʱ��ʱ��
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //ʱ�ӷ�Ƶ���ӣ��������������������ʱ����Ҫ�õ�
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //����������ģʽ������Ϊ���ϼ���
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;            //�����ظ���������ֵΪ0���������ظ�����
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);             //��ʼ����ʱ��

    /*--------------------����ȽϽṹ���ʼ��---------------------*/
    TIM_OCInitTypeDef TIM_OCInitStructure; //������ʱ������ȽϽṹ��

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;             //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //ʹ������Ƚ�
    TIM_OCInitStructure.TIM_Pulse = 0;                            //���ó�ʼռ�ձ�
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;     //�������:TIM����Ƚϼ��Ը�(�ߵ�ƽ��Ч)

    TIM_OC1Init(TIM3, &TIM_OCInitStructure); //��ʼ������Ƚ�ͨ��1
    TIM_OC2Init(TIM3, &TIM_OCInitStructure); //��ʼ������Ƚ�ͨ��2
    TIM_OC3Init(TIM3, &TIM_OCInitStructure); //��ʼ������Ƚ�ͨ��3
    TIM_OC4Init(TIM3, &TIM_OCInitStructure); //��ʼ������Ƚ�ͨ��4

    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable); //ʹ��ͨ��1��CCR1�ϵ�Ԥװ�ؼĴ���
    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable); //ʹ��ͨ��2��CCR2�ϵ�Ԥװ�ؼĴ���
    TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable); //ʹ��ͨ��3��CCR3�ϵ�Ԥװ�ؼĴ���
    TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable); //ʹ��ͨ��4��CCR4�ϵ�Ԥװ�ؼĴ���

    GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //������ӳ��

    TIM_Cmd(TIM3, ENABLE);              //ʹ��TIM
    TIM_ARRPreloadConfig(TIM3, ENABLE); //ʹ��TIM1��ARR�ϵ�Ԥװ�ؼĴ���
    //TIM_CtrlPWMOutputs(TIM3, ENABLE);   //�����ʹ�ܣ���ʹ�õ���ͨ�ö�ʱ��������Ҫ�����ʹ��
}

/**
  * @brief	      ������ƺ���
  * @param	      motor_num ��������motor_1/motor_2/motor_3/motor_4��ѡ����Ƶ��1/2/3/4
  * @param	      speed_set PWM�ߵ�ƽ��ʱ�䡣���������ٶ��趨ֵ�����Ƶ��ת��.��Χ0-500
  * @retval       ��
  * @author       718 Lab
  */
void Motor_Run(int motor_num, int speed_set)
{
    switch (motor_num)
    {
    case motor_1:
        TIM_SetCompare1(TIM3, speed_set);
        break;
    case motor_2:
        TIM_SetCompare2(TIM3, speed_set);
        break;
    case motor_3:
        TIM_SetCompare3(TIM3, speed_set);
        break;
    case motor_4:
        TIM_SetCompare4(TIM3, speed_set);
        break;
    default:
        break;
    }
}

/**
  * @brief	      ������Ժ���
  * @param	      ��
  * @retval       ��
  * @author       718 Lab
  */
void Test_Motor(void)
{
    while (1)
    {
        Motor_Run(motor_1, 100);
        Motor_Run(motor_2, 200);
        Motor_Run(motor_3, 300);
        Motor_Run(motor_4, 400);
    }
}

