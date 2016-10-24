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
#include  "time.h"
#include  "ppi.h"
#include "nrf_delay.h"

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

		timer0_init();  // Timer0用于LED灯的亮灭 
    timer1_init();  // Timer1 定时器产生的偶数秒的事件
    timer2_init();  // Timer2定时器产生的奇数秒事件
    ppi_init();     // PPI事件重定向到计时器启动/停止任务

    NRF_POWER->TASKS_CONSTLAT = 1;//启用恒定延迟模式
    
    // Start clock.
    NRF_TIMER1->TASKS_START = 1;//开定时器1
    NRF_TIMER2->TASKS_START = 1;//开定时器2

    nrf_gpio_range_cfg_output(LED_START, LED_STOP);//设置LED灯的范围

    while (true)
    {		
			
		     NRF_TIMER0->TASKS_COUNT         = 1;//设置定时器为递增计数模式
        NRF_TIMER0->TASKS_CAPTURE[0]    = 1;//捕捉定时器值寄存器CC0

        nrf_gpio_port_write(NRF_GPIO_PORT_SELECT_PORT2, (uint8_t)NRF_TIMER0->CC[0]);//用CCO的值来通知LED灯

        nrf_delay_ms(100);//延迟100ms
	 
    }
}


/** @} */
