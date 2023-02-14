#include "usart.h"
#include "include.h"

/**
  * @brief        ���ڶ�Ӧ��Ƕ�������жϿ����� NVIC ��ʼ������
  * @param        ��
  * @retval       ��
  * @author       718 Lab
***/

static void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    /* Ƕ�������жϿ�������ѡ�� */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    /* ���� USART Ϊ�ж�Դ */
    NVIC_InitStructure.NVIC_IRQChannel = USART_IRQ;
    /* �������ȼ�*/
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    /* �����ȼ� */
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    /* ʹ���ж� */
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    /* ��ʼ������NVIC */
    NVIC_Init(&NVIC_InitStructure);
}

/**
  * @brief        ���ڶ�Ӧ�� GPIO �����봮�������ʹ��
  * @param        ��
  * @retval       ��
  * @author       718 Lab
***/
void USART_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    // �򿪴���GPIO��ʱ��
    USART_GPIO_APBxClkCmd(USART_GPIO_CLK, ENABLE);

    // �򿪴��������ʱ��
    USART_APBxClkCmd(USART_CLK, ENABLE);

    // ��USART Tx��GPIO����Ϊ���츴��ģʽ
    GPIO_InitStructure.GPIO_Pin = USART_TX_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(USART_TX_GPIO_PORT, &GPIO_InitStructure);

    // ��USART Rx��GPIO����Ϊ��������ģʽ
    GPIO_InitStructure.GPIO_Pin = USART_RX_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(USART_RX_GPIO_PORT, &GPIO_InitStructure);

    // ���ô��ڵĹ�������
    // ���ò�����
    USART_InitStructure.USART_BaudRate = USART_BAUDRATE;
    // ����֡�����ֳ�
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    // ����ֹͣλ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    // ����У��λ
    USART_InitStructure.USART_Parity = USART_Parity_No;
    // ����Ӳ��������
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    // ���ù���ģʽ���շ�һ��
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    // ��ɴ��ڵĳ�ʼ������
    USART_Init(USARTx, &USART_InitStructure);

    // �����ж����ȼ�����
    NVIC_Configuration();

    // ʹ�ܴ��ڽ����ж�
    USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);

    // ʹ�ܴ���
    USART_Cmd(USARTx, ENABLE);
}

/**
  * @brief        �����жϷ�����(Ŀǰ�ǽ��ܻ��Թ���)
  * @param        ��
  * @retval       ��
  * @note         �����жϻ������������״̬, ���ʹ�����������͵Ĵ����жϼǵ�Ҫ���жϷ�����
  * @author       718 Lab
***/

void Stright_on (int speed,int time)
	{
	
	TIM_SetCompare3(TIM3, speed);//  back left up
				
		  TIM_SetCompare2(TIM3, speed);//    back right  up
		 
	    TIM_SetCompare1(SERVO2_TIM, speed);    // ǰ��
 
      TIM_SetCompare4(SERVO3_TIM, speed); // ǰ��
						Delay_MS(time);
			TIM_SetCompare3(TIM3, 0);//  back left up
				
		  TIM_SetCompare2(TIM3, 0);//    back right  up
		 
	    TIM_SetCompare1(SERVO2_TIM, 0);    // ǰ��
 
      TIM_SetCompare4(SERVO3_TIM, 0); // ǰ��
	
	}		
	void Stright_down (int speed,int time)
	{
		TIM_SetCompare4(TIM3, speed);// �����
					
	     				
			TIM_SetCompare1(TIM3, speed);//    �Һ���
			 TIM_SetCompare2(SERVO2_TIM, speed);    // ��ǰ��
					

     TIM_SetCompare3(SERVO3_TIM, speed); // ��ǰ��
			
					Delay_MS(time);
			TIM_SetCompare4(TIM3, 0);//  back left up		
					
	     				
			TIM_SetCompare1(TIM3, 0);//    back right  up	
			 TIM_SetCompare2(SERVO2_TIM, 0);    // ǰ��
					

     TIM_SetCompare3(SERVO3_TIM, 0); // ǰ��

	}
	void Turn_left (void)
	{
		TIM_SetCompare4(TIM3, 20000);// ����ֵ�ת
		TIM_SetCompare3(SERVO3_TIM, 20000); // ��ǰ�ֵ�ת
		
		
		
		TIM_SetCompare1(SERVO2_TIM, 20000);    // ��ǰ��
 
//      TIM_SetCompare4(SERVO3_TIM, 0); // ��ǰ��
//				
//				TIM_SetCompare3(TIM3, 0);//  back left up
				
		  TIM_SetCompare2(TIM3, 20000);//    back right  up
				
		Delay_MS(8000);
				
			 TIM_SetCompare1(SERVO2_TIM, 0);    // ��ǰ��
 
     TIM_SetCompare4(TIM3, 0);// ����ֵ�ת
		TIM_SetCompare3(SERVO3_TIM, 0); // ��ǰ�ֵ�ת
				
			
				
		  TIM_SetCompare2(TIM3, 0);//    back right  up
	}
	void Turn_right (void)
	{
		TIM_SetCompare1(TIM3, 20000);//    �Һ��ֵ�ת
	 TIM_SetCompare2(SERVO2_TIM, 20000);    // ��ǰ�ֵ�ת
		
		
		
//		 TIM_SetCompare1(SERVO2_TIM, 0);    // ��ǰ��
 
      TIM_SetCompare4(SERVO3_TIM, 20000); // ��ǰ��
				
				TIM_SetCompare3(TIM3, 20000);//  back left up
				
//		  TIM_SetCompare2(TIM3, 0);//    back right  up
				
					Delay_MS(8000);
				
		//		TIM_SetCompare1(SERVO2_TIM, 0);    // ��ǰ��
			TIM_SetCompare1(TIM3, 0);//    �Һ��ֵ�ת
	 TIM_SetCompare2(SERVO2_TIM, 0);    // ��ǰ�ֵ�ת
 
      TIM_SetCompare4(SERVO3_TIM,0); // ��ǰ��
				
				TIM_SetCompare3(TIM3, 0);//  back left up
				
	//	  TIM_SetCompare2(TIM3, 0);//    back right  up
	}
	void Microleft(void)
	{
		TIM_SetCompare1(SERVO2_TIM, 20000);    // ��ǰ��
 
      TIM_SetCompare4(SERVO3_TIM, 0); // ��ǰ��
				
				TIM_SetCompare3(TIM3, 0);//  back left up
				
		  TIM_SetCompare2(TIM3, 20000);//    back right  up
				
					Delay_MS(300);
				
				TIM_SetCompare1(SERVO2_TIM, 0);    // ��ǰ��
 
      TIM_SetCompare4(SERVO3_TIM,0); // ��ǰ��
				
				TIM_SetCompare3(TIM3, 0);//  back left up
				
		  TIM_SetCompare2(TIM3, 0);//    back right  up
	}
		
void Microright(void)
{
	TIM_SetCompare1(SERVO2_TIM, 0);    // ��ǰ��
 
      TIM_SetCompare4(SERVO3_TIM, 20000); // ��ǰ��
				
				TIM_SetCompare3(TIM3, 20000);//  back left up
				
		  TIM_SetCompare2(TIM3, 0);//    back right  up
				Delay_MS(300);
				
			 TIM_SetCompare1(SERVO2_TIM, 0);    // ��ǰ��
 
      TIM_SetCompare4(SERVO3_TIM, 0); // ��ǰ��
				
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
			if(ucTemp=='A')//��ת
			{
			Stright_on(20000,500);
			}		
			else if(ucTemp=='B')//����
			{
		   Stright_down(20000,500);
			} 
		
			
		 else	if(ucTemp=='C')//��������A1
			{	
				TIM_SetCompare1(SERVO1_TIM, 1500); //�ʹ�С�۲���
				TIM_SetCompare2(SERVO1_TIM, 1000); //��۲���
				
				
				
				
			} 
			else if(ucTemp=='D')//����A2
			{
				TIM_SetCompare2(SERVO1_TIM, 2400); //���ˮƽ
			 TIM_SetCompare1(SERVO1_TIM, 1200); //С��΢��
				
			}
			else if(ucTemp=='E')//����
			 flag=0;
			
			else if(ucTemp=='G')
			 //��������
	{
//		TIM_SetCompare1(SERVO1_TIM, 1500); //�ʹ�С�۲���
//		Delay_MS(20000);	
//		TIM_SetCompare2(SERVO1_TIM, 1000); //��۲���
	//	Delay_MS(20000);
    TIM_SetCompare2(SERVO1_TIM, 1000);		
		Stright_on(20000,100);
		
		TIM_SetCompare2(SERVO1_TIM, 2400); //���ˮƽ
			TIM_SetCompare1(SERVO1_TIM, 1200); //С��΢��
		TIM_SetCompare1(SERVO1_TIM, 2000); //С��΢��
		
		Delay_MS(20000);
		
	}		
			else if(ucTemp=='H')
	
	{
		TIM_SetCompare1(SERVO1_TIM, 1500); //�ʹ�С�۲���
		Delay_MS(20000);	 
		TIM_SetCompare2(SERVO1_TIM, 1200); //��۲���
	}
		else if(ucTemp=='I')
		{
			
TIM_SetCompare1(SERVO1_TIM, 1000); //�ʹ�С������	
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
			
		TIM_SetCompare1(SERVO1_TIM, 2500); //�ߴ�С�۷���
   
			
		}		 
		
    }
	}

	
	
//����ֹͣ����
void emg_stop(void)
{
	
	    TIM_SetCompare3(TIM3, 0);//  back left up
				
		  TIM_SetCompare2(TIM3, 0);//    back right  up
		 
	    TIM_SetCompare1(SERVO2_TIM, 0);    // ǰ��
 
      TIM_SetCompare4(SERVO3_TIM, 0); // ǰ��
	
	
}
void dropback(void)
{
	Stright_down (20000,200);
	Turn_left();
}

/**
  * @brief        ���ڷ���һ���ַ�
  * @param        pUSARTx    ָ�����ڽṹ��ָ��
  * @param        ch         �����͵��ַ�
  * @retval       ��
  * @author       718 Lab
***/
void Usart_SendByte(USART_TypeDef *pUSARTx, uint8_t ch)
{
    /* ����һ���ֽ����ݵ�USART */
    USART_SendData(pUSARTx, ch);

    /* �ȴ��������ݼĴ���Ϊ�� */
    while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET)
        ;
}

/**
  * @brief        ���ڷ��Ͷ����ַ���
  * @param        pUSARTx    ָ�����ڽṹ��ָ��
  * @param        str        �����͵��ַ���
  * @retval       ��
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

    /* �ȴ�������� */
    while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET)
        ;
}

/**
  * @brief        ���ڷ���һ�� 16 λ�Ǹ�����
  * @param        pUSARTx  ָ�����ڽṹ��ָ��
  * @param        ch       �����͵� 16 λ�Ǹ�����
  * @retval       ��
  * @author       718 Lab
***/
void Usart_SendHalfWord(USART_TypeDef *pUSARTx, uint16_t ch)
{
    uint8_t temp_h, temp_l;

    /* ȡ���߰�λ */
    temp_h = (ch & 0XFF00) >> 8;
    /* ȡ���Ͱ�λ */
    temp_l = ch & 0XFF;

    /* ���͸߰�λ */
    USART_SendData(pUSARTx, temp_h);
    while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET)
        ;

    /* ���͵Ͱ�λ */
    USART_SendData(pUSARTx, temp_l);
    while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET)
        ;
}

/**
  * @brief        �ض��� C �⺯�� printf ������, �ض�����ʹ�� printf ����
  * @param        ch ʵ�������û���ʱ���Բ��ù�
  * @param        f  ʵ�������û���ʱ���Բ��ù�
  * @retval       ʵ�������û���ʱ���Բ��ù�
  * @author       718 Lab
***/
int fputc(int ch, FILE *f)
{
    /* ����һ���ֽ����ݵ����� */
    USART_SendData(USARTx, (uint8_t)ch);

    /* �ȴ�������� */
    while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET)
        ;

    return (ch);
}

/**
  * @brief        �ض���c�⺯�� scanf �����ڣ���д����ʹ�� scanf/getchar �Ⱥ���
  * @param        f ʵ�������û���ʱ���Բ��ù�
  * @retval       ʵ�������û���ʱ���Բ��ù�
  * @author       718 Lab
***/
int fgetc(FILE *f)
{
    /* �ȴ������������� */
    while (USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) == RESET);

    return (int)USART_ReceiveData(USARTx);
}

/**
  * @brief        �� ADC ����ɼ���������ͨ�����ڴ�ӡ�����ڵ���������
  * @param        ��
  * @retval       ��
  * @note         ����ʹ��ǰ�о�һ���������ȷ����ʵ�ֵ�ȷʵ������ʵ�ֵĹ���
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
