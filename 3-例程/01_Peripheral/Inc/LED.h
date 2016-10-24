#ifndef __LED_H
#define	__LED_H

#include "nrf52.h"

#define LED_START      22


#define LED_0          22
#define LED_1          23
#define LED_2          24

#define LED_STOP       24

void LED_Init(void);
void LED_Open(int LED_X);
void LED_Close(int LED_X);
void LED_Toggle(int LED_X);
//void LED2_Open(void);
//void LED2_Close(void);
//void LED2_Toggle(void);



#endif /* __LED_H */
