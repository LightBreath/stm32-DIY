#include "oled.h"
#include "delay.h"
#include "oled_font.h"
#include "include.h"

#if 1 //创建一�?�?折叠的代码块用于存放IIC操作函数

void IIC_Start(void) //传输开�?
{
    OLED_SCL_H;
    OLED_SDA_H;
    OLED_SDA_L;
    OLED_SCL_L;
}

void IIC_Stop(void) //传输结束
{
    OLED_SCL_L;
    OLED_SDA_L;
    OLED_SCL_H;
    OLED_SDA_H;
}

void IIC_Waitback(void) //等待应答
{
    OLED_SCL_H;
    OLED_SCL_L;
}

void IIC_SendByte(char Byte) //传输一个字节
{
    OLED_SCL_L;
    for (int a = 0; a < 8; a++)
    {
        if (Byte & 0x80)
        {
            OLED_SDA_H;
        }
        else
        {
            OLED_SDA_L;
        }
        Byte <<= 1;
        OLED_SCL_H;
        OLED_SCL_L;
    }
}

void IIC_WriteData(uint8_t data, char identifying)
{
    IIC_Start();
    IIC_SendByte(0x78);
    IIC_Waitback();
    if (identifying)
    {
        IIC_SendByte(0x40);
    }
    else
    {
        IIC_SendByte(0x00);
    }
    IIC_Waitback();
    IIC_SendByte(data);
    IIC_Waitback();
    IIC_Stop();
}

#endif
/*

*/
void OLED_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(OLED_SCL_CLK, ENABLE); //打开GPIOB的时钟
    RCC_APB2PeriphClockCmd(OLED_SDA_CLK, ENABLE); //打开GPIOB的时钟

    GPIO_InitStructure.GPIO_Pin = OLED_SCL_PIN | OLED_SDA_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; //开漏输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(OLED_SCL_PORT, &GPIO_InitStructure);
    GPIO_Init(OLED_SDA_PORT, &GPIO_InitStructure);

    GPIO_SetBits(OLED_SCL_PORT, OLED_SCL_PIN); //使GPIOB10 11输出高电平
    GPIO_SetBits(OLED_SDA_PORT, OLED_SDA_PIN);

    Delay_Init();
    //以下代码与oled通信= =初始化
    IIC_WriteData(0xAE, OLED_COMMAND); //display off
    IIC_WriteData(0x00, OLED_COMMAND); //set low column address
    IIC_WriteData(0x10, OLED_COMMAND); //set high column address
    IIC_WriteData(0x40, OLED_COMMAND); //set start line address
    IIC_WriteData(0xB0, OLED_COMMAND); //set page address
    IIC_WriteData(0x81, OLED_COMMAND); //contract control
    IIC_WriteData(0xFF, OLED_COMMAND); //128
    IIC_WriteData(0xA1, OLED_COMMAND); //set segment remap
    IIC_WriteData(0xA6, OLED_COMMAND); //normal / reverse
    IIC_WriteData(0xA8, OLED_COMMAND); //set multiplex ratio(1 to 64)
    IIC_WriteData(0x3F, OLED_COMMAND); //1/32 duty
    IIC_WriteData(0xC8, OLED_COMMAND); //Com scan direction
    IIC_WriteData(0xD3, OLED_COMMAND); //set display offset
    IIC_WriteData(0x00, OLED_COMMAND); //
    IIC_WriteData(0xD5, OLED_COMMAND); //set osc division
    IIC_WriteData(0x80, OLED_COMMAND); //
    IIC_WriteData(0xD8, OLED_COMMAND); //set area color mode off
    IIC_WriteData(0x05, OLED_COMMAND); //
    IIC_WriteData(0xD9, OLED_COMMAND); //Set Pre-Charge Period
    IIC_WriteData(0xF1, OLED_COMMAND); //
    IIC_WriteData(0xDA, OLED_COMMAND); //set com pin configuartion
    IIC_WriteData(0x12, OLED_COMMAND); //
    IIC_WriteData(0xDB, OLED_COMMAND); //set Vcomh
    IIC_WriteData(0x30, OLED_COMMAND); //
    IIC_WriteData(0x8D, OLED_COMMAND); //set charge pump enable
    IIC_WriteData(0x14, OLED_COMMAND); //
    IIC_WriteData(0xAF, OLED_COMMAND); //--turn on oled panel
    OLED_clear();
}

void OLED_clear(void)
{
    for (int i = 0; i < 8; i++)
    {
        IIC_WriteData(0xb0 + i, OLED_COMMAND);
        IIC_WriteData(0x00, OLED_COMMAND);
        IIC_WriteData(0x10, OLED_COMMAND);
        for (int n = 0; n < 128; n++)
        {
            IIC_WriteData(0, OLED_DATA);
        }
    }
}
void OLED_setpos(uint8_t x, uint8_t y)
{
    IIC_WriteData(0xb0 + y, OLED_COMMAND);
    IIC_WriteData(((x & 0xf0) >> 4) | 0x10, OLED_COMMAND);
    IIC_WriteData((x & 0x0f), OLED_COMMAND);
}
void OLED_show6x8char(uint8_t x, uint8_t y, char character)
{
    character -= ' '; //消除字库�?的偏�?
    OLED_setpos(x, y);
    for (int a = 0; a < 6; a++)
    {
        IIC_WriteData(char6X8[character][a], OLED_DATA);
    }
}
void OLED_show8x16char(uint8_t x, uint8_t y, char character)
{
    character -= ' '; //消除字库�?的偏�?
    OLED_setpos(x, y);
    for (int a = 0; a < 8; a++)
    {
        IIC_WriteData(char8X16[character][a], OLED_DATA);
    }
    OLED_setpos(x, y + 1);
    for (int a = 0; a < 8; a++)
    {
        IIC_WriteData(char8X16[character][a + 8], OLED_DATA);
    }
}
void OLED_show6x8string(uint8_t x, uint8_t y, char *string)
{
    OLED_setpos(x, y);
    int location = 0;
    while (string[location] != '\0')
    {
        for (int a = 0; a < 6; a++)
        {
            IIC_WriteData(char6X8[string[location] - ' '][a], OLED_DATA);
        }
        location++;
    }
}
void OLED_show8x16string(uint8_t x, uint8_t y, char *string)
{
    int location = 0;
    OLED_setpos(x, y);
    while (string[location] != '\0')
    {
        for (int a = 0; a < 8; a++)
        {
            IIC_WriteData(char8X16[string[location] - ' '][a], OLED_DATA);
        }
        location++;
    }
    location = 0;
    OLED_setpos(x, y + 1);
    while (string[location] != '\0')
    {
        for (int a = 0; a < 8; a++)
        {
            IIC_WriteData(char8X16[string[location] - ' '][a + 8], OLED_DATA);
        }
        location++;
    }
}
void OLED_show6x8number(uint8_t x, uint8_t y, int number)
{
    OLED_setpos(x, y);
    if (number < 0) //显示负号并使数字变�??
    {
        for (int a = 0; a < 6; a++)
        {
            IIC_WriteData(char6X8['-' - ' '][a], OLED_DATA);
        }
        number = -number;
    }
    else
    {
        for (int a = 0; a < 6; a++) //显示空白字�??
        {
            IIC_WriteData(char6X8[0][a], OLED_DATA);
        }
    }
    //�?换数字为字�?�串
    char num[20];
    num[19] = '\0';
    int a = 18;
    while (1)
    {
        if (!number) //当数字为0时跳�?
        {
            break;
        }
        num[a] = number % 10 + '0';
        number /= 10;
        a--;
    }
    OLED_show6x8string(x + 6, y, num + a + 1);
}
void OLED_show8x16number(uint8_t x, uint8_t y, int number)
{
    if (number < 0) //显示负号并使数字变�??
    {
        OLED_show8x16char(x, y, '-');
        number = -number;
    }
    else
    {
        OLED_show8x16char(x, y, ' ');
    }
    //�?换数字为字�?�串
    char num[20];
    num[19] = '\0';
    int a = 18;
    while (1)
    {
        if (!number) //当数字为0时跳�?
        {
            break;
        }
        num[a] = number % 10 + '0';
        number /= 10;
        a--;
    }
    OLED_show8x16string(x + 6, y, num + a + 1);
}
void OLED_writedata(uint8_t data)
{
    IIC_WriteData(data, OLED_DATA);
}
void Test_ADC_OLED(void)
{
    do
    {
        OLED_show8x16string(80, 4, "718");
        OLED_show8x16string(80, 6, "LAB");
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
        char txt[20];
        sprintf(txt, "1: %.2fV", ADC_ConvertedValueLocal[0]);
        OLED_show6x8string(0, 0, txt);
        sprintf(txt, "2: %.2fV", ADC_ConvertedValueLocal[1]);
        OLED_show6x8string(0, 1, txt);
        sprintf(txt, "3: %.2fV", ADC_ConvertedValueLocal[2]);
        OLED_show6x8string(0, 2, txt);
        sprintf(txt, "4: %.2fV", ADC_ConvertedValueLocal[3]);
        OLED_show6x8string(0, 3, txt);
        sprintf(txt, "5: %.2fV", ADC_ConvertedValueLocal[4]);
        OLED_show6x8string(0, 4, txt);
        sprintf(txt, "6: %.2fV", ADC_ConvertedValueLocal[5]);
        OLED_show6x8string(0, 5, txt);
        sprintf(txt, "7: %.2fV", ADC_ConvertedValueLocal[6]);
        OLED_show6x8string(0, 6, txt);
        sprintf(txt, "8: %.2fV", ADC_ConvertedValueLocal[7]);
        OLED_show6x8string(0, 7, txt);
        sprintf(txt, "9 : %.2fV", ADC_ConvertedValueLocal[8]);
        OLED_show6x8string(60, 0, txt);
        sprintf(txt, "10: %.2fV", ADC_ConvertedValueLocal[9]);
        OLED_show6x8string(60, 1, txt);
        sprintf(txt, "11: %.2fV", ADC_ConvertedValueLocal[10]);
        OLED_show6x8string(60, 2, txt);
        sprintf(txt, "12: %.2fV", ADC_ConvertedValueLocal[11]);
        OLED_show6x8string(60, 3, txt);
        Delay_MS(1000);
    } while (1);
}
