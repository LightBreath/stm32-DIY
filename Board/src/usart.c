#include "usart.h"
#include "include.h"

/**
  * @brief        串口对应的嵌套向量中断控制器 NVIC 初始化函数
  * @param        无
  * @retval       无
  * @author       718 Lab
***/

static void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    /* 嵌套向量中断控制器组选择 */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    /* 配置 USART 为中断源 */
    NVIC_InitStructure.NVIC_IRQChannel = USART_IRQ;
    /* 抢断优先级*/
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    /* 子优先级 */
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    /* 使能中断 */
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    /* 初始化配置NVIC */
    NVIC_Init(&NVIC_InitStructure);
}

/**
  * @brief        串口对应的 GPIO 配置与串口外设的使能
  * @param        无
  * @retval       无
  * @author       718 Lab
***/
void USART_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    // 打开串口GPIO的时钟
    USART_GPIO_APBxClkCmd(USART_GPIO_CLK, ENABLE);

    // 打开串口外设的时钟
    USART_APBxClkCmd(USART_CLK, ENABLE);

    // 将USART Tx的GPIO配置为推挽复用模式
    GPIO_InitStructure.GPIO_Pin = USART_TX_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(USART_TX_GPIO_PORT, &GPIO_InitStructure);

    // 将USART Rx的GPIO配置为浮空输入模式
    GPIO_InitStructure.GPIO_Pin = USART_RX_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(USART_RX_GPIO_PORT, &GPIO_InitStructure);

    // 配置串口的工作参数
    // 配置波特率
    USART_InitStructure.USART_BaudRate = USART_BAUDRATE;
    // 配置帧数据字长
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    // 配置停止位
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    // 配置校验位
    USART_InitStructure.USART_Parity = USART_Parity_No;
    // 配置硬件流控制
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    // 配置工作模式，收发一起
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    // 完成串口的初始化配置
    USART_Init(USARTx, &USART_InitStructure);

    // 串口中断优先级配置
    NVIC_Configuration();

    // 使能串口接收中断
    USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);

    // 使能串口
    USART_Cmd(USARTx, ENABLE);
}

/**
  * @brief        串口中断服务函数(目前是接受回显功能)
  * @param        无
  * @retval       无
  * @note         串口中断还会出现其他的状态, 如果使能了其它类型的串口中断记得要改中断服务函数
  * @author       718 Lab
***/

void Stright_on (int speed,int time)
	{
	
	TIM_SetCompare3(TIM3, speed);//  back left up
				
		  TIM_SetCompare2(TIM3, speed);//    back right  up
		 
	    TIM_SetCompare1(SERVO2_TIM, speed);    // 前轮
 
      TIM_SetCompare4(SERVO3_TIM, speed); // 前轮
						Delay_MS(time);
			TIM_SetCompare3(TIM3, 0);//  back left up
				
		  TIM_SetCompare2(TIM3, 0);//    back right  up
		 
	    TIM_SetCompare1(SERVO2_TIM, 0);    // 前轮
 
      TIM_SetCompare4(SERVO3_TIM, 0); // 前轮
	
	}		
	void Stright_down (int speed,int time)
	{
		TIM_SetCompare4(TIM3, speed);// 左后轮
					
	     				
			TIM_SetCompare1(TIM3, speed);//    右后轮
			 TIM_SetCompare2(SERVO2_TIM, speed);    // 右前轮
					

     TIM_SetCompare3(SERVO3_TIM, speed); // 左前轮
			
					Delay_MS(time);
			TIM_SetCompare4(TIM3, 0);//  back left up		
					
	     				
			TIM_SetCompare1(TIM3, 0);//    back right  up	
			 TIM_SetCompare2(SERVO2_TIM, 0);    // 前轮
					

     TIM_SetCompare3(SERVO3_TIM, 0); // 前轮

	}
	void Turn_left (void)
	{
		TIM_SetCompare4(TIM3, 20000);// 左后轮倒转
		TIM_SetCompare3(SERVO3_TIM, 20000); // 左前轮倒转
		
		
		
		TIM_SetCompare1(SERVO2_TIM, 20000);    // 右前轮
 
//      TIM_SetCompare4(SERVO3_TIM, 0); // 左前轮
//				
//				TIM_SetCompare3(TIM3, 0);//  back left up
				
		  TIM_SetCompare2(TIM3, 20000);//    back right  up
				
		Delay_MS(8000);
				
			 TIM_SetCompare1(SERVO2_TIM, 0);    // 右前轮
 
     TIM_SetCompare4(TIM3, 0);// 左后轮倒转
		TIM_SetCompare3(SERVO3_TIM, 0); // 左前轮倒转
				
			
				
		  TIM_SetCompare2(TIM3, 0);//    back right  up
	}
	void Turn_right (void)
	{
		TIM_SetCompare1(TIM3, 20000);//    右后轮倒转
	 TIM_SetCompare2(SERVO2_TIM, 20000);    // 右前轮倒转
		
		
		
//		 TIM_SetCompare1(SERVO2_TIM, 0);    // 右前轮
 
      TIM_SetCompare4(SERVO3_TIM, 20000); // 左前轮
				
				TIM_SetCompare3(TIM3, 20000);//  back left up
				
//		  TIM_SetCompare2(TIM3, 0);//    back right  up
				
					Delay_MS(8000);
				
		//		TIM_SetCompare1(SERVO2_TIM, 0);    // 右前轮
			TIM_SetCompare1(TIM3, 0);//    右后轮倒转
	 TIM_SetCompare2(SERVO2_TIM, 0);    // 右前轮倒转
 
      TIM_SetCompare4(SERVO3_TIM,0); // 左前轮
				
				TIM_SetCompare3(TIM3, 0);//  back left up
				
	//	  TIM_SetCompare2(TIM3, 0);//    back right  up
	}
	void Microleft(void)
	{
		TIM_SetCompare1(SERVO2_TIM, 20000);    // 右前轮
 
      TIM_SetCompare4(SERVO3_TIM, 0); // 左前轮
				
				TIM_SetCompare3(TIM3, 0);//  back left up
				
		  TIM_SetCompare2(TIM3, 20000);//    back right  up
				
					Delay_MS(300);
				
				TIM_SetCompare1(SERVO2_TIM, 0);    // 右前轮
 
      TIM_SetCompare4(SERVO3_TIM,0); // 左前轮
				
				TIM_SetCompare3(TIM3, 0);//  back left up
				
		  TIM_SetCompare2(TIM3, 0);//    back right  up
	}
		
void Microright(void)
{
	TIM_SetCompare1(SERVO2_TIM, 0);    // 右前轮
 
      TIM_SetCompare4(SERVO3_TIM, 20000); // 左前轮
				
				TIM_SetCompare3(TIM3, 20000);//  back left up
				
		  TIM_SetCompare2(TIM3, 0);//    back right  up
				Delay_MS(300);
				
			 TIM_SetCompare1(SERVO2_TIM, 0);    // 右前轮
 
      TIM_SetCompare4(SERVO3_TIM, 0); // 左前轮
				
				TIM_SetCompare3(TIM3, 0);//  back left up
				
		  TIM_SetCompare2(TIM3, 0);//    back right  up
}
	
void USART_IRQHandler(void)
{
  extern int flag;
	uint8_t ucTemp;
    if (USART_GetITStatus(USARTx, USART_IT_RXNE) != RESET)
    {
        ucTemp = USART_ReceiveData(USARTx);
//			
			if(ucTemp=='A')//正转
			{
			Stright_on(20000,500);
			}		
			else if(ucTemp=='B')//倒车
			{
		   Stright_down(20000,500);
			} 
		
			
		 else	if(ucTemp=='C')//铲球连招A1
			{	
				TIM_SetCompare1(SERVO1_TIM, 1500); //低处小臂铲球
				TIM_SetCompare2(SERVO1_TIM, 1000); //大臂铲球
				
				
				
				
			} 
			else if(ucTemp=='D')//铲球A2
			{
				TIM_SetCompare2(SERVO1_TIM, 2400); //大臂水平
			 TIM_SetCompare1(SERVO1_TIM, 1200); //小臂微收
				
			}
			else if(ucTemp=='E')//接手
			 flag=0;
			
			else if(ucTemp=='G')
			 //铲球连招
	{
//		TIM_SetCompare1(SERVO1_TIM, 1500); //低处小臂铲球
//		Delay_MS(20000);	
//		TIM_SetCompare2(SERVO1_TIM, 1000); //大臂铲球
	//	Delay_MS(20000);
    TIM_SetCompare2(SERVO1_TIM, 1000);		
		Stright_on(20000,100);
		
		TIM_SetCompare2(SERVO1_TIM, 2400); //大臂水平
			TIM_SetCompare1(SERVO1_TIM, 1200); //小臂微收
		TIM_SetCompare1(SERVO1_TIM, 2000); //小臂微放
		
		Delay_MS(20000);
		
	}		
			else if(ucTemp=='H')
	
	{
		TIM_SetCompare1(SERVO1_TIM, 1500); //低处小臂铲球
		Delay_MS(20000);	 
		TIM_SetCompare2(SERVO1_TIM, 1200); //大臂铲球
	}
		else if(ucTemp=='I')
		{
			
TIM_SetCompare1(SERVO1_TIM, 1000); //低处小臂收球	
			Delay_MS(1000);	 
   
			
		}		 
		
		else if(ucTemp=='K')
		{
			Microleft();
		}
		else if(ucTemp=='L')
		{
			Microright();
		}
		else if(ucTemp=='J')
		{
			
		TIM_SetCompare1(SERVO1_TIM, 2500); //高处小臂放球
   
			
		}		 
		
    }
	}

	
	
//紧急停止函数
void emg_stop(void)
{
	
	    TIM_SetCompare3(TIM3, 0);//  back left up
				
		  TIM_SetCompare2(TIM3, 0);//    back right  up
		 
	    TIM_SetCompare1(SERVO2_TIM, 0);    // 前轮
 
      TIM_SetCompare4(SERVO3_TIM, 0); // 前轮
	
	
}
void dropback(void)
{
	Stright_down (20000,200);
	Turn_left();
}

/**
  * @brief        串口发送一个字符
  * @param        pUSARTx    指定串口结构体指针
  * @param        ch         待发送的字符
  * @retval       无
  * @author       718 Lab
***/
void Usart_SendByte(USART_TypeDef *pUSARTx, uint8_t ch)
{
    /* 发送一个字节数据到USART */
    USART_SendData(pUSARTx, ch);

    /* 等待发送数据寄存器为空 */
    while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET)
        ;
}

/**
  * @brief        串口发送定长字符串
  * @param        pUSARTx    指定串口结构体指针
  * @param        str        待发送的字符串
  * @retval       无
  * @author       718 Lab
***/
void Usart_SendString(USART_TypeDef *pUSARTx, char *str)
{
    unsigned int k = 0;
    do
    {
        Usart_SendByte(pUSARTx, *(str + k));
        k++;
    } while (*(str + k) != '\0');

    /* 等待发送完成 */
    while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET)
        ;
}

/**
  * @brief        串口发送一个 16 位非负整数
  * @param        pUSARTx  指定串口结构体指针
  * @param        ch       待发送的 16 位非负整数
  * @retval       无
  * @author       718 Lab
***/
void Usart_SendHalfWord(USART_TypeDef *pUSARTx, uint16_t ch)
{
    uint8_t temp_h, temp_l;

    /* 取出高八位 */
    temp_h = (ch & 0XFF00) >> 8;
    /* 取出低八位 */
    temp_l = ch & 0XFF;

    /* 发送高八位 */
    USART_SendData(pUSARTx, temp_h);
    while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET)
        ;

    /* 发送低八位 */
    USART_SendData(pUSARTx, temp_l);
    while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET)
        ;
}

/**
  * @brief        重定向 C 库函数 printf 到串口, 重定向后可使用 printf 函数
  * @param        ch 实际意义用户暂时可以不用管
  * @param        f  实际意义用户暂时可以不用管
  * @retval       实际意义用户暂时可以不用管
  * @author       718 Lab
***/
int fputc(int ch, FILE *f)
{
    /* 发送一个字节数据到串口 */
    USART_SendData(USARTx, (uint8_t)ch);

    /* 等待发送完毕 */
    while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET)
        ;

    return (ch);
}

/**
  * @brief        重定向c库函数 scanf 到串口，重写向后可使用 scanf/getchar 等函数
  * @param        f 实际意义用户暂时可以不用管
  * @retval       实际意义用户暂时可以不用管
  * @author       718 Lab
***/
int fgetc(FILE *f)
{
    /* 等待串口输入数据 */
    while (USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) == RESET);

    return (int)USART_ReceiveData(USARTx);
}

/**
  * @brief        将 ADC 外设采集到的数据通过串口打印到串口调试助手上
  * @param        无
  * @retval       无
  * @note         建议使用前研究一下这个函数确保它实现的确实是你想实现的功能
  * @author       718 Lab
***/
void Test_ADC_PRINTF(void)
{
   
        ADC_ConvertedValueLocal[0] = (float)ADC_ConvertedValue[0] / 4096 * 3.3 * 1.5;
        ADC_ConvertedValueLocal[1] = (float)ADC_ConvertedValue[1] / 4096 * 3.3 * 1.5;
        ADC_ConvertedValueLocal[2] = (float)ADC_ConvertedValue[2] / 4096 * 3.3 * 1.5;
        ADC_ConvertedValueLocal[3] = (float)ADC_ConvertedValue[3] / 4096 * 3.3 * 1.5;
        ADC_ConvertedValueLocal[4] = (float)ADC_ConvertedValue[4] / 4096 * 3.3 * 1.5;
        ADC_ConvertedValueLocal[5] = (float)ADC_ConvertedValue[5] / 4096 * 3.3 * 1.5;
        ADC_ConvertedValueLocal[6] = (float)ADC_ConvertedValue[6] / 4096 * 3.3 * 1.5;
        ADC_ConvertedValueLocal[7] = (float)ADC_ConvertedValue[7] / 4096 * 3.3 * 1.5;
        ADC_ConvertedValueLocal[8] = (float)ADC_ConvertedValue[8] / 4096 * 3.3 * 1.5;
        ADC_ConvertedValueLocal[9] = (float)ADC_ConvertedValue[9] / 4096 * 3.3 * 1.5;
        ADC_ConvertedValueLocal[10] = (float)ADC_ConvertedValue[10] / 4096 * 3.3 * 1.5;
        ADC_ConvertedValueLocal[11] = (float)ADC_ConvertedValue[11] / 4096 * 3.3 * 1.5;

//        printf("\r\n CH0 value = %f V \r\n", ADC_ConvertedValueLocal[0]);
//        printf("\r\n CH1 value = %f V \r\n", ADC_ConvertedValueLocal[1]);
//        printf("\r\n CH2 value = %f V \r\n", ADC_ConvertedValueLocal[2]);
//        printf("\r\n CH3 value = %f V \r\n", ADC_ConvertedValueLocal[3]);
//        printf("\r\n CH4 value = %f V \r\n", ADC_ConvertedValueLocal[4]);
//        printf("\r\n CH5 value = %f V \r\n", ADC_ConvertedValueLocal[5]);
//        printf("\r\n CH6 value = %f V \r\n", ADC_ConvertedValueLocal[6]);
//        printf("\r\n CH7 value = %f V \r\n", ADC_ConvertedValueLocal[7]);
//        printf("\r\n CH8 value = %f V \r\n", ADC_ConvertedValueLocal[8]);
//        printf("\r\n CH9 value = %f V \r\n", ADC_ConvertedValueLocal[9]);
//        printf("\r\n CH10 value = %f V \r\n", ADC_ConvertedValueLocal[10]);
//       printf("\r\n CH11 value = %f V \r\n", ADC_ConvertedValueLocal[11]);

       
   
}
