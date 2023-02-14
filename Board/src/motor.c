#include "motor.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"


/**
  * @brief	      电机初始化函数
  * @param        无
  * @retval       无
  * @author       718 Lab
  */
void TIM_MOTOR_Init(void)
{
    /* --------------输出比较通道1、2、3、4的GPIO初始化------------- */
    GPIO_InitTypeDef GPIO_InitStructure; //声明GPIO初始化结构体

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);                             //使能AFIO复用时钟	//使能重映射IO时钟
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);                         //shut JTAG
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_1 | GPIO_Pin_0; //设置GPIO管脚
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                                  //复用推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                                //设置输出频率
    GPIO_Init(GPIOB, &GPIO_InitStructure);                                           //初始化GPIO

    /*----------------------时基结构体初始化-----------------------*/
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; //声明定时器时基结构体

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //使能重映射定时器时钟

    /* 配置周期，这里配置为0.0005s。提示：Tout= ((arr+1)*(psc+1))/Tclk */
    TIM_TimeBaseStructure.TIM_Period = 20000 - 1;                 //定时器周期arr，即自动重装载寄存器的值
                                                                //累计TIM_Period+1个频率后产生一个更新或者中断
    TIM_TimeBaseStructure.TIM_Prescaler = 71;                   //定时器预分频器设置psc，时钟源经该预分频器才是定时器时钟
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //时钟分频因子，输出互补脉冲配置死区时间需要用到
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //计数器计数模式，设置为向上计数
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;            //设置重复计数器的值为0，不设置重复计数
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);             //初始化定时器

    /*--------------------输出比较结构体初始化---------------------*/
    TIM_OCInitTypeDef TIM_OCInitStructure; //声明定时器输出比较结构体

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;             //选择定时器模式:TIM脉冲宽度调制模式1
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //使能输出比较
    TIM_OCInitStructure.TIM_Pulse = 0;                            //设置初始占空比
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;     //输出极性:TIM输出比较极性高(高电平有效)

    TIM_OC1Init(TIM3, &TIM_OCInitStructure); //初始化输出比较通道1
    TIM_OC2Init(TIM3, &TIM_OCInitStructure); //初始化输出比较通道2
    TIM_OC3Init(TIM3, &TIM_OCInitStructure); //初始化输出比较通道3
    TIM_OC4Init(TIM3, &TIM_OCInitStructure); //初始化输出比较通道4

    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable); //使能通道1的CCR1上的预装载寄存器
    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable); //使能通道2的CCR2上的预装载寄存器
    TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable); //使能通道3的CCR3上的预装载寄存器
    TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable); //使能通道4的CCR4上的预装载寄存器

    GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //开启重映射

    TIM_Cmd(TIM3, ENABLE);              //使能TIM
    TIM_ARRPreloadConfig(TIM3, ENABLE); //使能TIM1在ARR上的预装载寄存器
    //TIM_CtrlPWMOutputs(TIM3, ENABLE);   //主输出使能，当使用的是通用定时器，不需要主输出使能
}

/**
  * @brief	      电机控制函数
  * @param	      motor_num 可以填入motor_1/motor_2/motor_3/motor_4来选择控制电机1/2/3/4
  * @param	      speed_set PWM高电平的时间。可以填入速度设定值来控制电机转速.范围0-500
  * @retval       无
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
  * @brief	      电机测试函数
  * @param	      无
  * @retval       无
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

