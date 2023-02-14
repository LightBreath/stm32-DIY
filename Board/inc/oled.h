#ifndef __OLED_H__
#define __OLED_H__
#include "stm32f10x.h"
/*
用户若需要修改引脚，
修改本处宏定义的引脚和
oled_init()函数中的初始化引脚即可
*/
#define OLED_SCL_H                      GPIO_SetBits(GPIOB, GPIO_Pin_8)   //SCL引脚输出高电平
#define OLED_SCL_L                      GPIO_ResetBits(GPIOB, GPIO_Pin_8) //SCL引脚输出低电平
#define OLED_SCL_PORT                   GPIOB
#define OLED_SCL_PIN                    GPIO_Pin_8
#define OLED_SCL_CLK                    RCC_APB2Periph_GPIOB

#define OLED_SDA_H                      GPIO_SetBits(GPIOB, GPIO_Pin_9)   //SDA引脚输出高电平
#define OLED_SDA_L                      GPIO_ResetBits(GPIOB, GPIO_Pin_9) //SDA引脚输出低电平
#define OLED_SDA_PORT                   GPIOB
#define OLED_SDA_PIN                    GPIO_Pin_9
#define OLED_SDA_CLK                    RCC_APB2Periph_GPIOB
/*
说明：初始化oled模块
*/
extern void OLED_init(void);

/*
说明：清除oled显示
*/
extern void OLED_clear(void);
extern void OLED_setpos(uint8_t x, uint8_t y);
extern void IIC_WriteData(uint8_t data, char identifying);

/*
说明：以6*8(8*16)的大小在oled上显示一个字符
参数：x 取值范围0~127
			y 取值范围0~7(8*16时范围为0-6)，与x一起决定显示位置
			character 你要显示的字符
*/
extern void OLED_show6x8char(uint8_t x, uint8_t y, char character);
extern void OLED_show8x16char(uint8_t x, uint8_t y, char character);
/*
说明：以6*8(8*16)的大小在oled上显示一个以'\0'字符结尾的字符串
参数：x 取值范围0~127
			y 取值范围0~7(8*16时范围为0-6)，与x一起决定显示位置
			string 你要显示的字符串
			
			该函数遇到'\0'字符才会结束。
*/
extern void OLED_show6x8string(uint8_t x, uint8_t y, char *string);
extern void OLED_show8x16string(uint8_t x, uint8_t y, char *string);
/*
说明：以6*8(8*16)的大小在oled上显示一个数字
参数：x 取值范围0~127
			y 取值范围0~7(8*16时为0-6)，与x一起决定显示位置
			number 用户要显示的数字，正负均可
*/
extern void OLED_show6x8number(uint8_t x, uint8_t y, int number);
extern void OLED_show8x16number(uint8_t x, uint8_t y, int number);
extern void Test_ADC_OLED(void);

#define OLED_COMMAND 0
#define OLED_DATA 1

#endif
