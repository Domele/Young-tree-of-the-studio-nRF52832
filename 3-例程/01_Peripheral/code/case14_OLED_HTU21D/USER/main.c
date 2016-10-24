/* Copyright (c) 2009 Nordic Semiconductor. All Rights Reserved.
 *
 * The information contained herein is property of Nordic Semiconductor ASA.
 * Terms and conditions of usage are described in detail in NORDIC
 * SEMICONDUCTOR STANDARD SOFTWARE LICENSE AGREEMENT.
 *
 * Licensees are granted free, non-transferable use of the information. NO
 * WARRANTY of ANY KIND is provided. This heading must NOT be removed from
 * the file.
 *
 */

/** @file
* @brief Example template project.
* @defgroup nrf_templates_example Example Template
*
*/

#include <stdbool.h>
#include <stdint.h>

#include <stdio.h>
#include <string.h>

#include "nrf.h"
#include "nrf_gpio.h"
#include "nordic_common.h"
#include "nrf_delay.h"
#include "app_error.h"
#include "app_timer.h"
#include "app_util_platform.h"
#include "boards.h"
#include "bsp.h"


#include "oled.h"
#include "uart.h"
#include "simple_uart.h"
//#include "LIS2DH12.h"
#include "I2C.h"


/**
 * @brief Function for application main entry.
 */
int main(void)
{
	//unsigned char i;
	char buffer[20];
	//oled 引脚初始化
	OLED_GPIO_Init();
	//oled   显示初始化
	LCD_Init();

	
	//uart 初始化
	 USART_Configuration();
	//uart 接受中断
	uart_exit();

	
 
//	for(i=0; i<8; i++)
//	{
//		LCD_P16x16Ch(i*16,0,i);  //????
//	} 
    LCD_P8x16Str(0,0,"Nordic_OLED"); 
	LCD_P8x16Str(0,2,"nRF52832EK_PRO"); 
	LCD_P6x8Str(0,4,"HTU21D demo"); 
	//LCD_P6x8Str(0,5,"T=");
	//LCD_P6x8Str(0,6,"H=");
	//LCD_P6x8Str(0,7,"z=");

    printf("OLED_init_ok!\r\n");
	//Gsensor_init();
	I2C_htu21d_init();
	printf("I2C_htu21d_init_ok!\r\n");
	I2C_HTU21_reset();
	delay_ms(200);

	//printf("ID=%d\r\n",LIS2DH12_Get_Chip_Id());
    while (true)
    {

		HTU21D_Func();
		//printf("T=%03.1F,H=%03.1F\r\n",temp_value,humi_value);
		sprintf(buffer,"Temp=%03.1F",temp_value);
		LCD_P6x8Str(0,5,(uint8_t *)buffer);
		sprintf(buffer,"Humi=%03.1F",humi_value);
		LCD_P6x8Str(0,6,(uint8_t *)buffer);
		strncpy(buffer,"\0",10);
		LCD_DLY_ms(1000);
    }
}



