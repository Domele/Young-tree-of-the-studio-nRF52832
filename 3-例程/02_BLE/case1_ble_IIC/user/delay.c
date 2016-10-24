#include "delay.h"

#include "compiler_abstraction.h"
#include "nrf.h"
#include "nrf_delay.h"

void delay_us(unsigned long ms)
{
	nrf_delay_us(ms);
}
/*lint --e{438} "Variable not used" */
void delay_ms(uint32_t volatile number_of_ms)
{
    while(number_of_ms != 0) {
        number_of_ms--;
        nrf_delay_us(999);
    }
}	



//void delay_ms(unsigned long ms)    //ÑÓÊ±º¯Êý
//{                         
//	unsigned long a;
//	while(ms)
//	{
//		a=2585;
//		while(a--);
//		ms--;
//	}
//}


