#ifndef __SPI_MASTER_CONFIG_H__
#define __SPI_MASTER_CONFIG_H__
#include "pca10036.h"
/*

*/

	/* GPIO pin number for SPI */
//	#define SPI_PSELSCK0              22   /*!< GPIO pin number for SPI clock (note that setting this to 31 will only work for loopback purposes as it not connected to a pin) */
//	#define SPI_PSELMOSI0             23   /*!< GPIO pin number for Master Out Slave In    */
//	#define SPI_PSELMISO0             21   /*!< GPIO pin number for Master In Slave Out    */
//	#define SPI_PSELSS0               24  //SPI_CS   /*!< GPIO pin number for Slave Select           */

//	#define SPIS_CSN_PIN   SPI_PSELSS0    // SPI CSN signal. 
//	#define SPIS_MISO_PIN  SPI_PSELMISO0    // SPI MISO signal. 
//	#define SPIS_MOSI_PIN  SPI_PSELMOSI0    // SPI MOSI signal. 
//	#define SPIS_SCK_PIN   SPI_PSELSCK0    // SPI SCK signal. 

	#define SPI_PSELSS0   SPIS_CSN_PIN       // SPI CSN signal. 
	#define SPI_PSELMISO0 SPIS_MISO_PIN      // SPI MISO signal. 
	#define SPI_PSELMOSI0 SPIS_MOSI_PIN      // SPI MOSI signal. 
	#define SPI_PSELSCK0  SPIS_SCK_PIN       // SPI SCK signal. 


	//#include "board_config_pins.h"
	#ifndef SPI_MASTER_CONFIG_H
		#define SPI_MASTER_CONFIG_H

		#define SPI_OPERATING_FREQUENCY  ( 0x02000000UL << (uint32_t)Freq_1Mbps)  /*!< Slave clock frequency. */
		//#define SPI_OPERATING_FREQUENCY  ( 0x02000000UL << (uint32_t)Freq_500Kbps) 
		#define NUMBER_OF_TEST_BYTES     2    /*!< number of bytes to send to slave to test if Initialization was successful */
		#define TEST_BYTE                0xBB /*!< Randomly chosen test byte to transmit to spi slave */
		#define TIMEOUT_COUNTER          0x8000UL  /*!< timeout for getting rx bytes from slave */

		#ifdef SPI1
			/*  SPI1 */
			#define SPI_PSELSCK1              29   /*!< GPIO pin number for SPI clock              */
			#define SPI_PSELMOSI1             21   /*!< GPIO pin number for Master Out Slave In    */
			#define SPI_PSELMISO1             23   /*!< GPIO pin number for Master In Slave Out    */
			#define SPI_PSELSS1               28   /*!< GPIO pin number for Slave Select           */
		#endif
	//#define DEBUG
		#ifdef DEBUG
		#define DEBUG_EVENT_READY_PIN0    10    /*!< when DEBUG is enabled, this GPIO pin is toggled everytime READY_EVENT is set for SPI0, no toggling means something has gone wrong */
		#define DEBUG_EVENT_READY_PIN1    11    /*!< when DEBUG is enabled, this GPIO pin is toggled everytime READY_EVENT is set for SPI1, no toggling means something has gone wrong */



	/** @def  TX_RX_MSG_LENGTH
	 * number of bytes to transmit and receive. This amount of bytes will also be tested to see that
	 * the received bytes from slave are the same as the transmitted bytes from the master */
		#define TX_RX_MSG_LENGTH   100

	/** @def ERROR_PIN_SPI0
	 * This pin is set active high when there is an error either in TX/RX for SPI0 or if the received bytes does not totally match the transmitted bytes.
	 * This functionality can be tested by temporarily disconnecting the MISO pin while running this example.
	 */
		#define ERROR_PIN_SPI0   8UL

	/** @def ERROR_PIN_SPI1
	 * This pin is set active high when there is an error either in TX/RX for SPI1 or if the received bytes does not totally match the transmitted bytes.
	 * This functionality can be tested by temporarily disconnecting the MISO pin while running this example.
	 */
		#define ERROR_PIN_SPI1   9UL
		#endif
	#endif

#endif /* SPI_MASTER_CONFIG_H */


