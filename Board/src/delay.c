#include "delay.h"
#include "include.h"

static uint8_t fac_us = 0;
static uint16_t fac_ms = 0;

/**
  * @brief        ��ʼ����ʱ����
  * @param        ��
  * @retval       ��
  * @author       718 Lab
***/
void Delay_Init(void)
{
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
    fac_us = SystemCoreClock / 8000000;
    fac_ms = (u16)fac_us * 1000;
}

/**
  * @brief        ΢�뼶��ʱ����
  * @param        nus һ�� 32 λ�޷���������ʾ��ʱʱ��(��λ΢��)
  * @retval       ��
  * @author       718 Lab
***/
void Delay_US(u32 nus)
{
    u32 temp;
    SysTick->LOAD = nus * fac_us;
    SysTick->VAL = 0x00;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
    do
    {
        temp = SysTick->CTRL;
    } while ((temp & 0x01) && !(temp & (1 << 16)));
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
    SysTick->VAL = 0X00;
}

/**
  * @brief        ���뼶��ʱ����
  * @param        nms һ�� 32 λ�޷���������ʾ��ʱʱ��(��λ����)
  * @retval       ��
  * @author       718 Lab
***/
void Delay_MS(u16 nms)
{
    u32 temp;
    SysTick->LOAD = (u32)nms * fac_ms;
    SysTick->VAL = 0x00;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
    do
    {
        temp = SysTick->CTRL;
    } while ((temp & 0x01) && !(temp & (1 << 16)));
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
    SysTick->VAL = 0X00;
}
