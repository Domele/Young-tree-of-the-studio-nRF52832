#include "nrf52.h"
#include "nrf_gpio.h"
#include "uart.h"
#include "simple_uart.h"
#include <stdarg.h>
#include <stdio.h>

//#include "led.h"



void USART_Configuration(void)//串口初始化函数
  {  

    simple_uart_config(RTS_PIN_NUMBER, TX_PIN_NUMBER, CTS_PIN_NUMBER, RX_PIN_NUMBER, HWFC);
 //   nrf_gpio_cfg_output(ERROR_PIN); // ERROR_PIN configured as output.

		}			
	
		
		

void uart_exit(void)
{
 
    NRF_UART0->INTENSET = UART_INTENSET_RXDRDY_Enabled << UART_INTENSET_RXDRDY_Pos;
    
    NVIC_SetPriority(UART0_IRQn, 1);
    NVIC_EnableIRQ(UART0_IRQn);

}
		
void UART0_IRQHandler(void)
{
    static uint8_t data_array;

    data_array = simple_uart_get();

       simple_uart_put(data_array);

	//	LED_Toggle(LED_1);
}
		
	
/************************************************************** 
* 函数名  : fputc()
* 描述    : 重定义putc函数，这样可以使用printf函数从串口1打印输出
* 输入    : None
* 输出    : None
* 返回    : None
* 作者    : 半打
* 创建日期: 2014.1.1
* 版本    : V1.00
*************************************************************/
int fputc(int ch, FILE *f)
{
		/* Place your implementation of fputc here */
		/* 发送一个字节的数据 */
		simple_uart_put((uint8_t)ch);
		/* 等待发送完成 */
		return ch;
}

/************************************************************** 
* 函数名  : fputc()
* 描述    : 重定义putc函数，这样可以使用printf函数从串口1获取数据
* 输入    : None
* 输出    : None
* 返回    : None
* 作者    : 半打
* 创建日期: 2014.1.1
* 版本    : V1.00
*************************************************************/
int fgetc(FILE *f)
{
		/* 等待串口1输入数据 */
		/* 返回接收到的数据 */
		return (int)simple_uart_get();
}
