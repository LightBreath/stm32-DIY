#include "servo.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "delay.h"

/**
  * @brief	      �߼���ʱ����ʼ��
  * @param        ��
  * @retval       ��
  * @author       718 Lab
  */
void TIM_SERVO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure; //GPIO��ʼ���ṹ��
    //����Ƚ�ͨ��1��2��3 GPIO��ʼ��
    RCC_APB2PeriphClockCmd(RCC_APBPeriph_TIMx_GPIOx1, ENABLE); //ʹ����������ʱ��
    RCC_APB2PeriphClockCmd(RCC_APBPeriph_TIMx_GPIOx2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APBPeriph_TIMx_GPIOx3, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); //shut JTAG

    GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                                                                  //�����������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                                                                //�������Ƶ��
    GPIO_InitStructure.GPIO_Pin = SERVO1_TIM_CH1_PIN | SERVO1_TIM_CH2_PIN | SERVO1_TIM_CH3_PIN | SERVO1_TIM_CH4_PIN; //����GPIO�ܽ�
    GPIO_Init(SERVO1_PORT, &GPIO_InitStructure);                                                                     //��ʼ��GPIO

    GPIO_InitStructure.GPIO_Pin = SERVO2_TIM_CH2_PIN | SERVO2_TIM_CH3_PIN | SERVO2_TIM_CH4_PIN; //����GPIO�ܽ�
    GPIO_Init(SERVO2_PORT, &GPIO_InitStructure);                                                //��ʼ��GPIO

    GPIO_InitStructure.GPIO_Pin = SERVO3_TIM_CH1_PIN; //����GPIO�ܽ�
    GPIO_Init(SERVO3_PORT, &GPIO_InitStructure);      //��ʼ��GPIO

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; //��ʱ��ʱ���ṹ��
    TIM_OCInitTypeDef TIM_OCInitStructure;         //��ʱ������ȽϽṹ��

    RCC_APB2PeriphClockCmd(RCC_APBPeriph_TIMx1, ENABLE); //ʹ�ܶ�ʱ��ʱ��
    RCC_APB1PeriphClockCmd(RCC_APBPeriph_TIMx2, ENABLE); //ʹ�ܶ�ʱ��ʱ��
    RCC_APB1PeriphClockCmd(RCC_APBPeriph_TIMx3, ENABLE);

    /*--------------------ʱ���ṹ���ʼ��-------------------------*/
    // �������ڣ���������Ϊ0.02s
    TIM_TimeBaseStructure.TIM_Period = 20000 - 1;               //�Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
    TIM_TimeBaseStructure.TIM_Prescaler = 71;                   //����CNT��������ʱ�� = Fck_int/(psc+1)
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //ʱ�ӷ�Ƶ���� ���������������������ʱ����Ҫ�õ�
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //����������ģʽ������Ϊ���ϼ���
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;            //�����ظ���������ֵΪ0���������ظ�����
    TIM_TimeBaseInit(SERVO1_TIM, &TIM_TimeBaseStructure);       //��ʼ����ʱ��
    TIM_TimeBaseInit(SERVO2_TIM, &TIM_TimeBaseStructure);       //��ʼ����ʱ��
    TIM_TimeBaseInit(SERVO3_TIM, &TIM_TimeBaseStructure);       //��ʼ����ʱ��
    /*--------------------����ȽϽṹ���ʼ��-------------------*/
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;             //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //ʹ������Ƚ�
    TIM_OCInitStructure.TIM_Pulse = 0;                            //���ó�ʼռ�ձ�
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;     //�������:TIM����Ƚϼ��Ը�(�ߵ�ƽ��Ч)

    TIM_OC1Init(SERVO1_TIM, &TIM_OCInitStructure);          //��ʼ������Ƚ�ͨ��1
    TIM_OC1PreloadConfig(SERVO1_TIM, TIM_OCPreload_Enable); //ʹ��ͨ��1��CCR4�ϵ�Ԥװ�ؼĴ���

    TIM_OC2Init(SERVO1_TIM, &TIM_OCInitStructure);          //��ʼ������Ƚ�ͨ��2
    TIM_OC2PreloadConfig(SERVO1_TIM, TIM_OCPreload_Enable); //ʹ��ͨ��2��CCR4�ϵ�Ԥװ�ؼĴ���

    TIM_OC3Init(SERVO1_TIM, &TIM_OCInitStructure);          //��ʼ������Ƚ�ͨ��3
    TIM_OC3PreloadConfig(SERVO1_TIM, TIM_OCPreload_Enable); //ʹ��ͨ��3��CCR4�ϵ�Ԥװ�ؼĴ���

    TIM_OC4Init(SERVO1_TIM, &TIM_OCInitStructure);          //��ʼ������Ƚ�ͨ��3
    TIM_OC4PreloadConfig(SERVO1_TIM, TIM_OCPreload_Enable); //ʹ��ͨ��3��CCR4�ϵ�Ԥװ�ؼĴ���

    TIM_OC1Init(SERVO2_TIM, &TIM_OCInitStructure);          //��ʼ������Ƚ�ͨ��1
    TIM_OC1PreloadConfig(SERVO2_TIM, TIM_OCPreload_Enable); //ʹ��ͨ��1��CCR4�ϵ�Ԥװ�ؼĴ���

    TIM_OC2Init(SERVO2_TIM, &TIM_OCInitStructure);          //��ʼ������Ƚ�ͨ��2
    TIM_OC2PreloadConfig(SERVO2_TIM, TIM_OCPreload_Enable); //ʹ��ͨ��2��CCR4�ϵ�Ԥװ�ؼĴ���

    TIM_OC3Init(SERVO2_TIM, &TIM_OCInitStructure);          //��ʼ������Ƚ�ͨ��3
    TIM_OC3PreloadConfig(SERVO2_TIM, TIM_OCPreload_Enable); //ʹ��ͨ��3��CCR4�ϵ�Ԥװ�ؼĴ���

    TIM_OC4Init(SERVO2_TIM, &TIM_OCInitStructure);          //��ʼ������Ƚ�ͨ��3
    TIM_OC4PreloadConfig(SERVO2_TIM, TIM_OCPreload_Enable); //ʹ��ͨ��3��CCR4�ϵ�Ԥװ�ؼĴ���

    TIM_OC1Init(SERVO3_TIM, &TIM_OCInitStructure);          //��ʼ������Ƚ�ͨ��1
    TIM_OC1PreloadConfig(SERVO3_TIM, TIM_OCPreload_Enable); //ʹ��ͨ��1��CCR4�ϵ�Ԥװ�ؼĴ���

    TIM_OC2Init(SERVO3_TIM, &TIM_OCInitStructure);          //��ʼ������Ƚ�ͨ��2
    TIM_OC2PreloadConfig(SERVO3_TIM, TIM_OCPreload_Enable); //ʹ��ͨ��2��CCR4�ϵ�Ԥװ�ؼĴ���

    TIM_OC3Init(SERVO3_TIM, &TIM_OCInitStructure);          //��ʼ������Ƚ�ͨ��3
    TIM_OC3PreloadConfig(SERVO3_TIM, TIM_OCPreload_Enable); //ʹ��ͨ��3��CCR4�ϵ�Ԥװ�ؼĴ���

    TIM_OC4Init(SERVO3_TIM, &TIM_OCInitStructure);          //��ʼ������Ƚ�ͨ��3
    TIM_OC4PreloadConfig(SERVO3_TIM, TIM_OCPreload_Enable); //ʹ��ͨ��3��CCR4�ϵ�Ԥװ�ؼĴ���

    TIM_Cmd(SERVO1_TIM, ENABLE);            //ʹ��TIM
    TIM_CtrlPWMOutputs(SERVO1_TIM, ENABLE); //�����ʹ�ܣ���ʹ�õ���ͨ�ö�ʱ��������Ҫ�����ʹ��

    TIM_Cmd(SERVO2_TIM, ENABLE);            //ʹ��TIM
    TIM_CtrlPWMOutputs(SERVO2_TIM, ENABLE); //�����ʹ�ܣ���ʹ�õ���ͨ�ö�ʱ��������Ҫ�����ʹ��

    TIM_Cmd(SERVO3_TIM, ENABLE);            //ʹ��TIM
    TIM_CtrlPWMOutputs(SERVO3_TIM, ENABLE); //�����ʹ�ܣ���ʹ�õ���ͨ�ö�ʱ��������Ҫ�����ʹ��
}

/**
  * @brief	      ������ƺ���
  * @param        ��
  * @retval       ��
  * @note         ʹ��ʱע��һ�¶����ֵ��ռ�ձȡ�PWMƵ�ʡ������Ƿ�Χ��Ӧ��ռ�ձ�
  * @author       718 Lab
  */
void Servo_Open(void)
{
    TIM_SetCompare1(SERVO1_TIM, 2000);
    TIM_SetCompare2(SERVO1_TIM, 2000);
    TIM_SetCompare3(SERVO1_TIM, 2000);
    TIM_SetCompare4(SERVO1_TIM, 2000);
    TIM_SetCompare1(SERVO2_TIM, 2000);
    TIM_SetCompare2(SERVO2_TIM, 2000);
    TIM_SetCompare3(SERVO2_TIM, 2000);
    TIM_SetCompare4(SERVO2_TIM, 2000);
    TIM_SetCompare1(SERVO3_TIM, 2000);
    TIM_SetCompare2(SERVO3_TIM, 2000);
    TIM_SetCompare3(SERVO3_TIM, 2000);
    TIM_SetCompare4(SERVO3_TIM, 2000);
}

/**
  * @brief	      ������ƺ���
  * @param        ��
  * @retval       ��
  * @note         ʹ��ʱע��һ�¶����ֵ��ռ�ձȡ�PWMƵ�ʡ������Ƿ�Χ��Ӧ��ռ�ձ�
  * @author       718 Lab
  */
void Servo_Close(void)
{
    TIM_SetCompare1(SERVO1_TIM, 1000);
    TIM_SetCompare2(SERVO1_TIM, 1000);
    TIM_SetCompare3(SERVO1_TIM, 1000);
    TIM_SetCompare4(SERVO1_TIM, 1000);
    TIM_SetCompare1(SERVO2_TIM, 2000);
    TIM_SetCompare2(SERVO2_TIM, 2000);
    TIM_SetCompare3(SERVO2_TIM, 2000);
    TIM_SetCompare4(SERVO2_TIM, 2000);
    TIM_SetCompare1(SERVO3_TIM, 2000);
    TIM_SetCompare2(SERVO3_TIM, 2000);
    TIM_SetCompare3(SERVO3_TIM, 2000);
    TIM_SetCompare4(SERVO3_TIM, 2000);
}

/**
  * @brief	      ������Ժ���
  * @param        ��
  * @retval       ��
  * @note         ʹ��ʱע��һ�¶����ֵ��ռ�ձȡ�PWMƵ�ʡ������Ƿ�Χ��Ӧ��ռ�ձ�
  * @author       718 Lab
  */
void Test_Servo(void)
{
    TIM_SetCompare1(SERVO1_TIM, 1000);
    TIM_SetCompare2(SERVO1_TIM, 1000);
    TIM_SetCompare3(SERVO1_TIM, 1000);
    TIM_SetCompare4(SERVO1_TIM, 1000);
    TIM_SetCompare1(SERVO2_TIM, 0);    // PA15
    TIM_SetCompare2(SERVO3_TIM, 3000); // PB3
    TIM_SetCompare3(SERVO3_TIM, 4000); // PB10
    TIM_SetCompare4(SERVO3_TIM, 5000); // PB11
    Delay_MS(1000);
}
