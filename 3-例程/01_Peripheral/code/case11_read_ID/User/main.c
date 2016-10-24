/* Copyright (c) 2014 Nordic Semiconductor. All Rights Reserved.
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
* 
* @defgroup gpiote_example_main main.c
* @{
* @ingroup nrf_gpiote_example
* @brief GPIOTE Example Application main file.
*
* This file contains the source code for a sample application using GPIOTE. 
*/


#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "led.h"
#include "uart.h"



/**
 * @brief Function for application main entry.
 */
int main(void)
{
			 uint32_t id1,id2;
			LED_Init();  //初始化led
			USART_Configuration();//初始化串口
	
	  id1=NRF_FICR->DEVICEID[0]; //读取id低31位
    id2=NRF_FICR->DEVICEID[1];//读取id高31位

    while (true)
    {

				printf("打印id_h：%lx\r\n",id1);
			printf("打印id_l：%lx\r\n",id2);
 // simple_uart_put(8);
    LED_Toggle(LED_1);
    nrf_delay_ms(1000);
   
	

    }
}


/** @} */
