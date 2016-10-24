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


void Delay_ms(void)
{

    unsigned int i,j;
     for (i=0;i<1000;i++)
	 	for(j=0;j<1000;j++);
	   

}

/**
 * @brief Function for application main entry.
 */
int main(void)
{

			LED_Init();
		//	LED_Open(LED_1);
	  //  LED_Open(LED_0) ;
		//	 LED_Open(LED_2) ;
    while (true)
    {
			//LED_Close(LED_1);
			
		
	    LED_Close(LED_0) ;
			 LED_Close(LED_1) ;
			 LED_Close(LED_2) ;

		
				Delay_ms();
			
			
				 LED_Open(LED_0) ;
			 LED_Open(LED_1) ;
			 LED_Open(LED_2) ;

			Delay_ms();
			

    }
}


/** @} */
