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
#include "led.h"
#include  "uart.h"
#include "nrf_delay.h"

#include "simple_uart.h"


/**
 * @brief Function for application main entry.
 */
int main(void)
{

			LED_Init();
		 USART_Configuration();
	
    while (1)
    {

			   LED_Toggle(LED_1);
	   	simple_uart_putstring(" 2016.06.15 ÐÇ»ã¿Æ¼¼£¡\r\n");
		//	simple_uart_put(0x55);
		  nrf_delay_ms(500);
        

    }
}


/** @} */
