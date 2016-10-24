#include <nrf52.h>
#include "delay.h"
#include "nrf_gpio.h"

//12  26
#define IIC_SCL_GPIO_Pin 12
#define IIC_SDA_GPIO_Pin 26
//#define HTU21D	0x80
#define HTU21D_I2CADDR	0x80
#define HTU21D_READTEMP	0xE3
#define HTU21D_READHUMI	0xE5
#define HTU21D_WRITEREG	0xE6
#define HTU21D_READREG	0xE7
#define HTU21D_RESET	0xFE

//extern uint8_t buf[2];
extern float temp_value;
extern float humi_value;



void SDA_OUT(void);
  
/** 
  * @brief  Set SDA Pin as Input Mode 
  * @retval None 
  */  
void SDA_IN(void);
  
/** 
  * @brief  read input voltage from SDA pin 
  * @retval None 
  */  
unsigned char SDA_READ(void);
  
/** 
  * @brief  output high form SDA pin 
  * @retval None 
  */  
void IIC_SDA_1(void);
  
/** 
  * @brief  output low form SDA pin 
  * @retval None 
  */  
void IIC_SDA_0(void);
  
/** 
  * @brief  output high form SCL pin 
  * @retval None 
  */  
void IIC_SCL_1(void);
  
/** 
  * @brief  output LOW form SCL pin 
  * @retval None 
  */  
void IIC_SCL_0(void);
  
/** 
* @brief  Simulate IIC conmunication :Create Start signal 
  * @retval None 
  */  
void IIC_Start(void);    
  
/** 
  * @brief  Simulate IIC conmunication : Create Stop signal 
  * @retval None 
  */  
void IIC_Stop(void);
  
/** 
* @brief  Simulate IIC conmunication : wait for target device's ACK 
* @retval ACK (0) : receive success 
* @retval NACK(1) : receive unsuccess 
  */  
unsigned char IIC_Wait_Ack(void);
  
/** 
  * @brief  Simulate IIC conmunication : make an ACK 
  * @retval None 
  */  
void IIC_Ack(void);
  
/** 
  * @brief  Simulate IIC conmunication : don't make an ACK 
  * @retval None 
  */  
void IIC_NAck(void);
  
/** 
  * @brief  Simulate IIC conmunication : Transmit one byte Data 
  * @param  txd: data to be transmit 
  * @retval None 
  */  
void IIC_Send_Byte(unsigned char txd);     
  
/** 
  * @brief  Simulate IIC conmunication : Receive one byte Data 
  * @param  ack: Whether transmit ACK 
  * @retval the data have been receive 
  *  ack=1 send ACK
  *  ack=0 send nACK
  */  

void I2C_htu21d_init(void);  
void I2C_HTU21_reset(void);
unsigned char IIC_Read_Byte(unsigned char ack);   
float I2C_TEMP_BufferRead(void);
float I2C_HUMI_BufferRead(void);

void HTU21D_Func(void);





