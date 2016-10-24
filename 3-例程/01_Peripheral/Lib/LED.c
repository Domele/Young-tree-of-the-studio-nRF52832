#include "nrf52.h"
#include "nrf_gpio.h"
#include "led.h"


/*
*name  :LED_Init
*  Function :  init led gpio
*/
void LED_Init(void)
{
  // Configure LED-pins as outputs
	int i;
	for(i=LED_START;i<=LED_STOP;i++)
	{
  nrf_gpio_cfg_output(i);
	}
}

/*
*name  :LED_Open
*  Function :  gpio set high
*/
void LED_Open(int LED_X)
{
	nrf_gpio_pin_set(LED_X);
}
/*
*name  :LED_Close
*  Function :  gpio set low
*/
void LED_Close(int LED_X)
{
	   nrf_gpio_pin_clear(LED_X);
	
}

/*
*name  :LED_Toggle
*  Function :  gpio Toggle  ·­×ª
*/
void LED_Toggle(int LED_X)
{
  nrf_gpio_pin_toggle(LED_X);
}
