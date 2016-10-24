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

		timer0_init();  // Timer0����LED�Ƶ����� 
    timer1_init();  // Timer1 ��ʱ��������ż������¼�
    timer2_init();  // Timer2��ʱ���������������¼�
    ppi_init();     // PPI�¼��ض��򵽼�ʱ������/ֹͣ����

    NRF_POWER->TASKS_CONSTLAT = 1;//���ú㶨�ӳ�ģʽ
    
    // Start clock.
    NRF_TIMER1->TASKS_START = 1;//����ʱ��1
    NRF_TIMER2->TASKS_START = 1;//����ʱ��2

    nrf_gpio_range_cfg_output(LED_START, LED_STOP);//����LED�Ƶķ�Χ

    while (true)
    {		
			
		     NRF_TIMER0->TASKS_COUNT         = 1;//���ö�ʱ��Ϊ��������ģʽ
        NRF_TIMER0->TASKS_CAPTURE[0]    = 1;//��׽��ʱ��ֵ�Ĵ���CC0

        nrf_gpio_port_write(NRF_GPIO_PORT_SELECT_PORT2, (uint8_t)NRF_TIMER0->CC[0]);//��CCO��ֵ��֪ͨLED��

        nrf_delay_ms(100);//�ӳ�100ms
	 
    }
}


/** @} */
