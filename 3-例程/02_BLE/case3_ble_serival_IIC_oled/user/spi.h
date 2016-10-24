#ifndef __SPI_H__
#define	__SPI_H__

#include "nrf51.h"
#include <stdio.h>
#include "nrf_gpio.h"
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include "spi_slave.h"
#include <spi_master.h>

#define SPIS_CSN_PIN   8    // SPI CSN signal. 
#define SPIS_MISO_PIN  9    // SPI MISO signal. 
#define SPIS_MOSI_PIN  10    // SPI MOSI signal. 
#define SPIS_SCK_PIN   11    // SPI SCK signal. 

/************************************** 定义部分 ****************************************************************/
#define TX_RX_BUF_LENGTH            1u            /**< SPI transaction buffer length. */
#define TX_BUF_SIZE                 4u            /**< SPI TX buffer size. */  

#define SPI_OPERATING_FREQUENCY  ( 0x02000000UL << (uint32_t)Freq_1Mbps )  
/*!< Slave clock frequency. */

extern uint8_t tx_data[TX_RX_BUF_LENGTH];          //SPI master tx_data
extern uint8_t rx_data[TX_RX_BUF_LENGTH];          //SPI master rx_data 
extern uint8_t cr;

void myspi_master_init(void);
void myspi_master_tx(uint8_t cz);
uint8_t myspi_master_rx(void);
uint8_t SPIx_ReadWriteByte(uint8_t TxData);


#endif 

