/*
*特别申明 次软件仅用于学习 
*Team：星汇科技
*作者 ： 半打猪猪
*版本： v1.0
*/



#include "nrf_gpio.h"
#include "led.h"
#include "key.h" 

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

			LED_Init();//led初始化
			KEY_Init();//按键初始化

    while (true)
    {

			if( KEY1_Down()== 0)//判定按键是否按下
			{
				 LED_Toggle(LED_0);
			} 
			

    }
}













/** @} */
