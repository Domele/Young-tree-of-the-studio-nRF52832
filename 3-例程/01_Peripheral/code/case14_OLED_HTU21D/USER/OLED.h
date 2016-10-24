#ifndef __OLED_H_
#define __OLED_H_


#include "nrf52.h"



#define LCD_SDA  23  //

#define LCD_POWER_EN   3

#define LCD_SCL  4

#define LCD_CS   22 //

#define LCD_RST  24

#define LCD_DC   3



#define XLevelL		0x00
#define XLevelH		0x10
#define XLevel	    ((XLevelH&0x0F)*16+XLevelL)
#define Max_Column	128
#define Max_Row		  64
#define	Brightness	0xCF 
#define X_WIDTH 128
#define Y_WIDTH 64

void LED_Init(void);
void LCD_Init(void);
void OLED_GPIO_Init(void);
void LCD_P6x8Str(unsigned char x, unsigned char y,unsigned char ch[]);
void LCD_P8x16Str(unsigned char x, unsigned y,unsigned char ch[]);
void LCD_P16x16Ch(unsigned char x, unsigned char y,unsigned char  N);
void Draw_BMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
void LCD_WrCmd(unsigned char cmd);
void LCD_DLY_ms(unsigned int ms);

//m^n函数
uint32_t mypow(uint8_t m,uint8_t n);			  
//显示2个数字
//x,y :起点坐标	 
//len :数字的位数
//size:字体大小
//mode:模式	0,填充模式;1,叠加模式
//num:数值(0~4294967295);	 		  
void OLED_ShowNum(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size);
//显示字符串
//x,y:起点坐标  
//*p:字符串起始地址
//用16字体
//void OLED_ShowString(uint8_t x,uint8_t y,uint8_t size,const uint8_t *p);
#endif 



