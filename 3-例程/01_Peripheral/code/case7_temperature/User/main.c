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

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "nrf_gpio.h"
#include "led.h"
#include  "uart.h"
#include "nrf_delay.h"
#include "nrf_temp.h"
#include "simple_uart.h"


/**
 * @brief Function for application main entry.
 */
int main(void)
{
	    unsigned int volatile temp;
	   unsigned char temp_h,temp_l;
		
	nrf_temp_init();   
			LED_Init();
		 USART_Configuration();
	
    while (1)
    {

		   NRF_TEMP->TASKS_START = 1; /** Start the temperature measurement. */

        /* Busy wait while temperature measurement is not finished, you can skip waiting if you enable interrupt for DATARDY event and read the result in the interrupt. */
        /*lint -e{845} // A zero has been given as right argument to operator '|'" */
        while (NRF_TEMP->EVENTS_DATARDY == 0)            
        {
            // Do nothing.
        }
        NRF_TEMP->EVENTS_DATARDY    = 0;  
        
        /**@note Workaround for PAN_028 rev2.0A anomaly 29 - TEMP: Stop task clears the TEMP register. */       
        temp                        = (nrf_temp_read()/4);
        
        /**@note Workaround for PAN_028 rev2.0A anomaly 30 - TEMP: Temp module analog front end does not power down when DATARDY event occurs. */
        NRF_TEMP->TASKS_STOP        = 1; /** Stop the temperature measurement. */

    
	//			temp_l =temp&0xff;
		//		temp_h = (temp>>8)&0xff;
				
		   printf(" 2016.06.15 星汇科技!\r\n");
		  printf("温度采样: %u \r\n",temp);
	
		
				
		  LED_Toggle(LED_1);
        nrf_delay_ms(500);

    }
}


/** @} */
