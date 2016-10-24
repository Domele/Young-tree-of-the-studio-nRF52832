#include "nrf52.h"
#include "nrf_gpio.h"
#include "Exit.h"
#include "led.h"

void EXIT_KEY_Init(void)
{

	 nrf_gpio_cfg_input(KEY_1,GPIO_PIN_CNF_PULL_Pullup);//���ùܽ�λ��������

    
    NVIC_EnableIRQ(GPIOTE_IRQn);//�ж�Ƕ������
	
    NRF_GPIOTE->CONFIG[0] =  (GPIOTE_CONFIG_POLARITY_HiToLo << GPIOTE_CONFIG_POLARITY_Pos)//Generate IN[n] event when falling edge on pin
                           | (KEY_1 << GPIOTE_CONFIG_PSEL_Pos)  //set Pin number
	
                           | (GPIOTE_CONFIG_MODE_Event << GPIOTE_CONFIG_MODE_Pos);//�ж����ã���ϸ˵����ο��̳̣�
    NRF_GPIOTE->INTENSET  = GPIOTE_INTENSET_IN0_Set << GPIOTE_INTENSET_IN0_Pos;// ʹ���ж�����:
}


void GPIOTE_IRQHandler(void)
{
   
    if ((NRF_GPIOTE->EVENTS_IN[0] == 1) && 
        (NRF_GPIOTE->INTENSET & GPIOTE_INTENSET_IN0_Msk))
    {
        NRF_GPIOTE->EVENTS_IN[0] = 0; //�ж��¼�����.
    }
   LED_Toggle(LED_0);//led�Ʒ�ת
}
