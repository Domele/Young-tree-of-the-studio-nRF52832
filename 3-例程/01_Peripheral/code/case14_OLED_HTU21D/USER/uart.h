#ifndef __UART_H
#define	__UART_H

#include "nrf52.h"
#include <stdio.h>
#include "pca10036.h"

//#define RX_PIN_NUMBER  8//12//9    // UART RX pin number.
//#define TX_PIN_NUMBER  6//13//11    // UART TX pin number.

//#define CTS_PIN_NUMBER 7//10   // UART Clear To Send pin number. Not used if HWFC is set to false
//#define RTS_PIN_NUMBER 5//12    // Not used if HWFC is set to false
//#define HWFC         false//  true//false // UART hardware flow control


void USART_Configuration(void);
void uart_exit(void);
void UART0_IRQHandler(void);

int fputc(int ch, FILE *f);
void UART_send_byte(uint8_t byte);
void UART_Send(uint8_t *Buffer, uint32_t Length);
uint8_t UART_Recive(void);

#endif /* __UART_H */
