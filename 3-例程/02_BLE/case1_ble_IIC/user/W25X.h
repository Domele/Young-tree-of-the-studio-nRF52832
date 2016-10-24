#ifndef __W25X_H__
#define	__W25X_H__
#include "spi_master_config.h" 
#include "bd_spi_master.h"
//#include "spi.h"
#include "nrf52.h"
#include <stdio.h>
#include "nrf_gpiote.h"
#include "nrf_gpio.h"
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>

////////////////////////////////////////////////////////////////////////////////// 	 
#define W25Q128 	0XEF17
//#define W25Q128 	0X17EF
//#define W25Q128 	0XE2FD
//#define W25Q128 	0XFDE2
//#define W25Q128 	0X7EF1
#define SPI_FLASH_TYPE	W25Q128
#define SPI_FLASH_CS    SPIS_CSN_PIN

#define	SPI_FLASH_CS_0 nrf_gpio_pin_clear(SPI_FLASH_CS);  //ѡ��FLASH	
#define	SPI_FLASH_CS_1 nrf_gpio_pin_set(SPI_FLASH_CS);  //ѡ��FLASH	
////////////////////////////////////////////////////////////////////////////

//extern uint8_t SPI_FLASH_BUF[4096];
//W25X16��д
#define FLASH_ID SPI_FLASH_TYPE
//ָ���
#define W25X_WriteEnable		0x06 
#define W25X_WriteDisable		0x04 
#define W25X_ReadStatusReg		0x05 
#define W25X_WriteStatusReg		0x01 
#define W25X_ReadData			0x03 
#define W25X_FastReadData		0x0B 
#define W25X_FastReadDual		0x3B 
#define W25X_PageProgram		0x02 
#define W25X_BlockErase			0xD8 
#define W25X_SectorErase		0x20 
#define W25X_ChipErase			0xC7 
#define W25X_PowerDown			0xB9 
#define W25X_ReleasePowerDown	0xAB 
#define W25X_DeviceID			0xAB 
#define W25X_ManufactDeviceID	0x90 
#define W25X_JedecDeviceID		0x9F 

uint8_t SPIx_ReadWriteByte(uint8_t TxData);
void SPI_Flash_Init(void);
uint16_t SPI_Flash_ReadID(void);  	    //��ȡFLASH ID
uint8_t	 SPI_Flash_ReadSR(void);        //��ȡ״̬�Ĵ��� 
void SPI_FLASH_Write_SR(uint8_t sr);  	//д״̬�Ĵ���
void SPI_FLASH_Write_Enable(void);  //дʹ�� 
void SPI_FLASH_Write_Disable(void);	//д����
void SPI_Flash_Write_NoCheck(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite);
void SPI_Flash_Read(uint8_t* pBuffer,uint32_t ReadAddr,uint16_t NumByteToRead);   //��ȡflash
//void SPI_Flash_Write(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite);//д��flash
void SPI_Flash_Erase_Chip(void);    	  //��Ƭ����
void SPI_Flash_Erase_Sector(uint32_t Dst_Addr);//��������
void SPI_Flash_Wait_Busy(void);           //�ȴ�����
void SPI_Flash_PowerDown(void);           //�������ģʽ
void SPI_Flash_WAKEUP(void);			  //����


#endif 
