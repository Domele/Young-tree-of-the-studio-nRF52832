/*
*�ر����� �����������ѧϰ 
*Team���ǻ�Ƽ�
*���� �� �������
*�汾�� v1.0
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

			LED_Init();//led��ʼ��
			KEY_Init();//������ʼ��

    while (true)
    {

			if( KEY1_Down()== 0)//�ж������Ƿ���
			{
				 LED_Toggle(LED_0);
			} 
			

    }
}













/** @} */
