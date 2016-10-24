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
#endif 

