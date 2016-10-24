#include "spi.h"

uint8_t tx_data[TX_RX_BUF_LENGTH] = {0};          //SPI master tx_data
uint8_t rx_data[TX_RX_BUF_LENGTH] = {0};          //SPI master rx_data 
uint8_t cr = 0;



void myspi_master_init(void)
{
	uint32_t config_mode;
	nrf_gpio_cfg_output(SPIS_SCK_PIN);                                     //设置管脚的模式
	nrf_gpio_cfg_output(SPIS_MOSI_PIN);
	nrf_gpio_cfg_input(SPIS_MISO_PIN, NRF_GPIO_PIN_NOPULL);
	nrf_gpio_cfg_output(SPIS_CSN_PIN);
	
	/* Configure pins, frequency and mode */
	NRF_SPI0->PSELSCK  = SPIS_SCK_PIN;                                     //设置管脚的插口
	NRF_SPI0->PSELMOSI = SPIS_MOSI_PIN;
	NRF_SPI0->PSELMISO = SPIS_MISO_PIN;
	nrf_gpio_pin_set(SPIS_CSN_PIN); /* disable Set slave select (inactive high) */
	NRF_SPI0->FREQUENCY = (uint32_t) SPI_OPERATING_FREQUENCY;               //设置频率
	config_mode = (SPI_CONFIG_CPHA_Leading << SPI_CONFIG_CPHA_Pos) | 
	              (SPI_CONFIG_CPOL_ActiveHigh << SPI_CONFIG_CPOL_Pos);      //设置模式
	NRF_SPI0->CONFIG = (config_mode | (SPI_CONFIG_ORDER_LsbFirst << SPI_CONFIG_ORDER_Pos));
	NRF_SPI0->INTENSET = (SPI_INTENSET_READY_Enabled << SPI_INTENSET_READY_Pos);
	NRF_SPI0->EVENTS_READY = 0U;
	NVIC_ClearPendingIRQ(SPI0_TWI0_IRQn);
	NVIC_EnableIRQ(SPI0_TWI0_IRQn);
  NRF_SPI0->ENABLE = (SPI_ENABLE_ENABLE_Enabled << SPI_ENABLE_ENABLE_Pos);
}

void SPI0_TWI0_IRQHandler(void)
{
	if(NRF_SPI0->EVENTS_READY != 0)
	{
		NRF_SPI0->EVENTS_READY = 0;
	}
}

/******************************************** SPI收发部分 *******************************************************/
void myspi_master_tx(uint8_t cz)                    //SPI master发送函数 -> OK                       //SPI master
{
	nrf_gpio_pin_clear(SPIS_CSN_PIN);                   //拉低电平 -> OK
	while(!(NRF_SPI0->EVENTS_READY == 0U));
	NRF_SPI0->TXD = (uint32_t)cz; 
	nrf_delay_ms(1);	
	nrf_gpio_pin_set(SPIS_CSN_PIN);                 //拉高电平 -> OK
}

uint8_t myspi_master_rx(void)                       //SPI master接收函数 -> OK
{
	uint8_t spi_data;
	nrf_gpio_pin_clear(SPIS_CSN_PIN);                 //拉低电平 -> OK
	while(NRF_SPI0->EVENTS_READY == 0U);
	spi_data = (uint8_t)NRF_SPI0->RXD;
 	nrf_gpio_pin_set(SPIS_CSN_PIN);                     //拉高电平 -> OK
	return spi_data;
}

uint8_t SPIx_ReadWriteByte(uint8_t TxData)
{		
	uint8_t retry=0;
	uint8_t spi_data;
	
	//nrf_gpio_pin_clear(SPIS_CSN_PIN);                   //拉低电平 -> OK
	while(!(NRF_SPI0->EVENTS_READY == 0U)){
		retry++;
		if(retry>200)return 0;	
	}
	NRF_SPI0->TXD = (uint32_t)TxData; 
	nrf_delay_ms(1);	
	//nrf_gpio_pin_set(SPIS_CSN_PIN);                 //拉高电平 -> OK
	
	retry=0;

	//nrf_gpio_pin_clear(SPIS_CSN_PIN);                 //拉低电平 -> OK
	while(NRF_SPI0->EVENTS_READY == 0U){
		retry++;
		if(retry>200)return 0;	
	}
	spi_data = (uint8_t)NRF_SPI0->RXD;
 	//nrf_gpio_pin_set(SPIS_CSN_PIN);                     //拉高电平 -> OK
	return spi_data;				    
}


