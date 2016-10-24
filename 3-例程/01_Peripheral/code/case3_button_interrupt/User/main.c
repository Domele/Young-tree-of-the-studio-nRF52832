/*
*特别申明 此软件仅用于学习 
*Team：星汇科技
*作者 ： 半打猪猪
*版本： v1.0
*/


#include "nrf_gpio.h"
#include "led.h"
#include "Exit.h" 

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

			LED_Init();//led初始化//	
		LED_Open(LED_0);
	   EXIT_KEY_Init();  //按键初始化
    while (true)
    {


    }
}













/** @} */
