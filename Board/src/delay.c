#include "delay.h"
#include "include.h"

static uint8_t fac_us = 0;
static uint16_t fac_ms = 0;

/**
  * @brief        初始化延时函数
  * @param        无
  * @retval       无
  * @author       718 Lab
***/
void Delay_Init(void)
{
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
    fac_us = SystemCoreClock / 8000000;
    fac_ms = (u16)fac_us * 1000;
}

/**
  * @brief        微秒级延时函数
  * @param        nus 一个 32 位无符号整数表示延时时间(单位微秒)
  * @retval       无
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
  * @brief        毫秒级延时函数
  * @param        nms 一个 32 位无符号整数表示延时时间(单位毫秒)
  * @retval       无
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
