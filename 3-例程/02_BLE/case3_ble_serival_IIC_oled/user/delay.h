#ifndef __DELAY_H
#define	__DELAY_H

#include "nrf52.h"
#include <stdio.h>
#include "nrf_gpio.h"
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
 #include "nrf_delay.h"

//typedef unsigned long  u32;
//typedef unsigned short u16;
//typedef unsigned char  u8;

void delay_us(unsigned long ms);    //ÑÓÊ±º¯Êý
//void delay_ms(unsigned long ms);
//void nrf_delay_ms(uint32_t volatile number_of_ms);
void delay_ms(uint32_t volatile number_of_ms);
	
#endif /* __DELAY_H */
