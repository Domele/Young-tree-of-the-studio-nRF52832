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
#include "LIS2DH12.h"



/**
 * @brief Function for application main entry.
 */
int main(void)
{
	//unsigned char i;
	uint16_t  DATA_X,DATA_Y,DATA_Z;
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
	LCD_P6x8Str(0,4,"G-sensor demo"); 
	LCD_P6x8Str(0,5,"x=");   
	LCD_P6x8Str(0,6,"y=");
	LCD_P6x8Str(0,7,"z=");   


	Gsensor_init();
	printf("OLED_init_ok!\r\n");

	printf("ID=%d\r\n",LIS2DH12_Get_Chip_Id());
    while (true)
    {
		DATA_X = LIS2DH12_Get_Chan_Data(LIS2DH12_ACC_CHAN_X);
		DATA_Y = LIS2DH12_Get_Chan_Data(LIS2DH12_ACC_CHAN_Y);
		DATA_Z = LIS2DH12_Get_Chan_Data(LIS2DH12_ACC_CHAN_Z);
		//	 printf("DATA_X=%d\r\n",DATA_X);
		//printf("DATA_X=%d DATA_Y=%d  DATA_Z=%d\r\n",DATA_X,DATA_Y,DATA_Z);
		OLED_ShowNum(12,5,DATA_X,5,12);
		OLED_ShowNum(12,6,DATA_Y,5,12);
		OLED_ShowNum(12,7,DATA_Z,5,12);
		LCD_DLY_ms(500);
    }
}



