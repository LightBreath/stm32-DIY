/**********************718 ����ʵ���ҿ���������*********************
*  ��д��718 ����ʵ����
*  ƽ̨��STM32F103RCT6
*  ˵�����������ߵ�ˮƽ���ޣ����в���֮�����������½⡣
*		 �����Ҷ࿴�������ֲᡣ
******************************************************************/
#include "stm32f10x.h"
#include "include.h"

// �� ADC1 ת���ĵ�ѹֵͨ�� DMA ��ʽ���� SRAM
extern __IO uint16_t ADC_ConvertedValue[NOFCHANEL];

// �ֲ����������ڱ���ת�������ĵ�ѹֵ
float ADC_ConvertedValueLocal[NOFCHANEL];
int flag=1;
int main()
{
	
	TIM_SERVO_Init();
	TIM_MOTOR_Init();
	
	USART_Config();
  Delay_Init(   );

	ADCx_Init();
	
	Delay_MS(500);
//while(1)
//{
//	Turn_left();
//	Delay_MS(5000);
//	Turn_right();
//	Delay_MS(5000);
//	Microleft();
//	Delay_MS(5000);
//	Microright();
//	Delay_MS(5000);
//	
//	
//}	

//	int i;
//	  TIM_SetCompare3(SERVO3_TIM, 20000); 
while(1)
{
	  if(flag==1)
		{
			
	//TIM_SetCompare2(SERVO1_TIM, 1800); 
			Test_ADC_PRINTF();
			if(Middle_light>2&&Left_light>1.5&&Right_light>1.5&&Leftstring<2&&Rightstring<1.5)
			{ 
			Stright_on(15000,10);
			}
			else if 
			 (Middle_light>1.5&&Left_light>3&&Right_light<1.5)
		{
			Microleft();
		 
		}
		else if (Middle_light<1.5&&Left_light<1.9&&Right_light>2.8)
		{																																																																																																																																																																										
		
			Microright();
		 
		}	
		else if (Rightstring>3.2)
		{
		
			Turn_right();
		 
		}	
		else if (Leftstring>3.1)
		{
		
			Turn_left();
		 
		}	
		else if (Block<3)
		{
		Stright_down(20000,500);
			Turn_left();
		
			
		 
		}	
		else if (Leftstring>3&&Rightstring>3&&Middle_light>3)
		{
		
			Turn_right();
		}
		
	else	
		 {
			
			Stright_on(10000,200);
			Delay_MS(100);
		 }
			
		
		
//		
	 }
	}		
//}

}
