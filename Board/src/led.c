#include "led.h"
#include "include.h"

/**
  * @brief        �� LED �ƶ�Ӧ�� GPIO �˿ڳ�ʼ������
  * @param        ��
  * @retval       ��
  * @author       718 Lab
***/
void LED_GPIO_Init(void)
{
    /* ����һ�� GPIO_InitTypeDef ���͵Ľṹ�� */
    GPIO_InitTypeDef GPIO_InitStructure;

    /* ���� LED ��ص� GPIO ����ʱ�� */
    RCC_APB2PeriphClockCmd(LED1_GPIO_CLK | LED2_GPIO_CLK | LED3_GPIO_CLK, ENABLE);
    /* ѡ��Ҫ���Ƶ� GPIO ���� */
    GPIO_InitStructure.GPIO_Pin = LED1_GPIO_PIN;
    /* ��������ģʽΪͨ��������� */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    /* ������������Ϊ 50MHz */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    /* ���ÿ⺯������ʼ�� GPIO */
    GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStructure);

    /* ѡ��Ҫ���Ƶ�GPIO���� */
    GPIO_InitStructure.GPIO_Pin = LED2_GPIO_PIN;
    /* ��ʼ��GPIO */
    GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStructure);

    /* ѡ��Ҫ���Ƶ� GPIO ���� */
    GPIO_InitStructure.GPIO_Pin = LED3_GPIO_PIN;
    /* ���ÿ⺯������ʼ�� GPIOF */
    GPIO_Init(LED3_GPIO_PORT, &GPIO_InitStructure);
}

/**
  * @brief        ���� LED ��Ӧ�� GPIO ���ŵ�״̬
  * @param        led   ��Ҫ���Ƶ� LED (LED1/LED2/LED3/LED_ALL)
  * @param        State ��Ҫ���õ�״̬(0 Ϊ�͵�ƽ 1 Ϊ�ߵ�ƽ)
  * @retval       ��
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
  * @brief        ���� LED ʵ����ˮ��
  * @param        ��
  * @retval       ��
  * @note         ������ˮ�������������, ���ܿ��ԸĽ�
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
