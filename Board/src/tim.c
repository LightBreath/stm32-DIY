#include "tim.h"
#include "led.h"

__IO uint64_t time; //使用 volatile 修饰,防止编译器优化
/*
 * 注意：TIM_TimeBaseInitTypeDef结构体里面有5个成员，TIM6和TIM7的寄存器里面只有
 * TIM_Prescaler和TIM_Period，所以使用TIM6和TIM7的时候只需初始化这两个成员即可
 * 另外三个成员是通用定时器和高级定时器才有的.
 *-----------------------------------------------------------------------------
 *typedef struct
 *{ TIM_Prescaler            都有
 *	TIM_CounterMode			 TIMx,x[6,7]没有，其他都有
 *  TIM_Period               都有
 *  TIM_ClockDivision        TIMx,x[6,7]没有，其他都有
 *  TIM_RepetitionCounter    TIMx,x[1,8,15,16,17]才有
 *}TIM_TimeBaseInitTypeDef;
 *-----------------------------------------------------------------------------
 */

/**
 * @brief        定时器中断初始化
 * @param        arr 自动重装载寄存器的值
 * @param        psc 时钟预分频数
 * @retval       无
 * @note         计数器频率为 freq = 72M/(psc+1) , 每隔 (arr+1)/freq 秒进入一次定时器中断
 * @author       718 Lab
*/
void TIM_Init(uint16_t arr, uint16_t psc)
{
    // 定时器TIM初始化
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_APBxClock_FUN(TIM_CLK, ENABLE);                         // 开启定时器时钟, 即内部时钟 CK_INT=72M
    TIM_TimeBaseStructure.TIM_Period = arr;                     // 自动重装载寄存器的值，累计 TIM_Period + 1 个频率后产生一个更新或者中断
    TIM_TimeBaseStructure.TIM_Prescaler = psc;                  // 设置时钟预分频数
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     // 时钟分频因子（互补输出，死区才用得到）
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // 计数器计数模式，选择向上计数
    TIM_TimeBaseInit(TIM, &TIM_TimeBaseStructure);              // 初始化定时器
    TIM_ClearFlag(TIM, TIM_FLAG_Update);                        // 清除计数器中断标志位
    TIM_ITConfig(TIM, TIM_IT_Update, ENABLE);                   // 使能定时器中断,允许更新中断
    TIM_Cmd(TIM, ENABLE);                                       // 使能计数器

    // 中断优先级NVIC设置
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);           // 设置 NVIC 中断分组 2:2 位抢占优先级, 2 位响应优先级
    NVIC_InitStructure.NVIC_IRQChannel = TIM_IRQ;             // 设置中断来源
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; // 设置主优先级为 0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;        // 设置抢占优先级为3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           // IRQ 通道被使能
    NVIC_Init(&NVIC_InitStructure);                           // 初始化 NVIC 寄存器
}

/**
 * @brief        定时器中断服务函数
 * @param        无
 * @retval       无
 * @author       718 Lab
*/
void TIM_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM, TIM_IT_Update)) // 检查 TIM3 更新中断发生与否
    {
        LED1_TOGGLE;
        TIM_ClearITPendingBit(TIM, TIM_IT_Update); // 清除 TIMx 更新中断标志
    }
    
}

/*********************************************END OF FILE**********************/
