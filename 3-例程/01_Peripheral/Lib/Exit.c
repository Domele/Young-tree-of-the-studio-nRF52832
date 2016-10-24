#include "nrf52.h"
#include "nrf_gpio.h"
#include "Exit.h"
#include "led.h"

void EXIT_KEY_Init(void)
{

	 nrf_gpio_cfg_input(KEY_1,GPIO_PIN_CNF_PULL_Pullup);//设置管脚位上拉输入

    
    NVIC_EnableIRQ(GPIOTE_IRQn);//中断嵌套设置
	
    NRF_GPIOTE->CONFIG[0] =  (GPIOTE_CONFIG_POLARITY_HiToLo << GPIOTE_CONFIG_POLARITY_Pos)//Generate IN[n] event when falling edge on pin
                           | (KEY_1 << GPIOTE_CONFIG_PSEL_Pos)  //set Pin number
	
                           | (GPIOTE_CONFIG_MODE_Event << GPIOTE_CONFIG_MODE_Pos);//中断配置（详细说明请参看教程）
    NRF_GPIOTE->INTENSET  = GPIOTE_INTENSET_IN0_Set << GPIOTE_INTENSET_IN0_Pos;// 使能中断类型:
}


void GPIOTE_IRQHandler(void)
{
   
    if ((NRF_GPIOTE->EVENTS_IN[0] == 1) && 
        (NRF_GPIOTE->INTENSET & GPIOTE_INTENSET_IN0_Msk))
    {
        NRF_GPIOTE->EVENTS_IN[0] = 0; //中断事件清零.
    }
   LED_Toggle(LED_0);//led灯翻转
}
