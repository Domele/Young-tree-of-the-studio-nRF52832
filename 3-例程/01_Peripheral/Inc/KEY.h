#ifndef __KEY_H
#define	__KEY_H

#include "nrf52.h"
#include "nrf_gpio.h"

#define KEY_1  3 
#define KEY_2  4


 
void KEY_Init(void);
uint8_t KEY1_Down(void);

#endif /* __KEY_H */

