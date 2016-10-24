#include <nrf52.h>
#include "delay.h"
#include "nrf_gpio.h"
#include "I2C.h"

float temp_value = 0;
float humi_value = 0;
//uint8_t buf[2];


void I2C_htu21d_init(void)
{
	nrf_gpio_cfg_output(IIC_SCL_GPIO_Pin);
	nrf_gpio_cfg_output(IIC_SDA_GPIO_Pin);
	nrf_gpio_pin_set(IIC_SCL_GPIO_Pin); //=1
	nrf_gpio_pin_set(IIC_SDA_GPIO_Pin); //=1
//	nrf_gpio_pin_clear(IIC_SCL_GPIO_Pin); //=0
//	nrf_gpio_pin_clear(IIC_SDA_GPIO_Pin); //=0
}

//nrf_gpio_cfg_output(SPI_PSELMOSI0);
//nrf_gpio_cfg_input(SPI_PSELMISO0, NRF_GPIO_PIN_NOPULL);
void SDA_OUT(void)    
{    
	nrf_gpio_cfg_output(IIC_SDA_GPIO_Pin);
}    
  
/** 
  * @brief  Set SDA Pin as Input Mode 
  * @retval None 
  */  
void SDA_IN(void)    
{    
	nrf_gpio_cfg_input(IIC_SDA_GPIO_Pin, NRF_GPIO_PIN_PULLUP);
}   
  
/** 
  * @brief  read input voltage from SDA pin 
  * @retval None 
  */  
unsigned char SDA_READ(void)  
{  
	return nrf_gpio_pin_read(IIC_SDA_GPIO_Pin);  
}  
  
/** 
  * @brief  output high form SDA pin 
  * @retval None 
  */  
void IIC_SDA_1(void)  
{
	nrf_gpio_pin_set(IIC_SDA_GPIO_Pin); 
}  
  
/** 
  * @brief  output low form SDA pin 
  * @retval None 
  */  
void IIC_SDA_0(void)  
{  
	nrf_gpio_pin_clear(IIC_SDA_GPIO_Pin); 
}  
  
/** 
  * @brief  output high form SCL pin 
  * @retval None 
  */  
void IIC_SCL_1(void)  
{  
	nrf_gpio_pin_set(IIC_SCL_GPIO_Pin);  
}  
  
/** 
  * @brief  output LOW form SCL pin 
  * @retval None 
  */  
void IIC_SCL_0(void)  
{  
	nrf_gpio_pin_clear(IIC_SCL_GPIO_Pin);    
}  
   
  
/** 
* @brief  Simulate IIC conmunication :Create Start signal 
  * @retval None 
  */  
void IIC_Start(void)  
{  
    SDA_OUT();     //sda output   
    IIC_SDA_1();            
    IIC_SCL_1();  
    delay_us(4);  
    IIC_SDA_0();   //START:when CLK is high,DATA change form high to low    
    delay_us(4);  
    IIC_SCL_0();   //hold scl line, prepare to transmit data   
}       
  
/** 
  * @brief  Simulate IIC conmunication : Create Stop signal 
  * @retval None 
  */  
void IIC_Stop(void)  
{  
    SDA_OUT();    //sda output mode    
    IIC_SCL_0();  
    IIC_SDA_0();  //STOP:when CLK is high DATA change form low to high   
    delay_us(4);  
    IIC_SCL_1();   
    IIC_SDA_1();  //indicate transmit over   
    delay_us(4);                               
}  
  
/** 
* @brief  Simulate IIC conmunication : wait for target device's ACK 
* @retval ACK (0) : receive success 
* @retval NACK(1) : receive unsuccess 
  */  
unsigned char IIC_Wait_Ack(void)  
{  
    unsigned char ucErrTime = 0;  
    SDA_IN();      //set as input mode   
    IIC_SDA_1();  
    delay_us(1);        
    IIC_SCL_1();  
    delay_us(1);      
    while(SDA_READ())  
    {  
        ucErrTime++;  
        if(ucErrTime > 250)  
        {  
            IIC_Stop();  
            return 1;  
        }  
    }  
    IIC_SCL_0(); //release scl line   
    return 0;    
}   
  
/** 
  * @brief  Simulate IIC conmunication : make an ACK 
  * @retval None 
  */  
void IIC_Ack(void)  
{  
    IIC_SCL_0();  
    SDA_OUT();  
    IIC_SDA_0();  
    delay_us(2);  
    IIC_SCL_1();  
    delay_us(2);  
    IIC_SCL_0();  
}  
  
/** 
  * @brief  Simulate IIC conmunication : don't make an ACK 
  * @retval None 
  */  
void IIC_NAck(void)  
{  
    IIC_SCL_0();  
    SDA_OUT();  
    IIC_SDA_1();  
    delay_us(2);  
    IIC_SCL_1();  
    delay_us(2);  
    IIC_SCL_0();  
}                                          
  
  
/** 
  * @brief  Simulate IIC conmunication : Transmit one byte Data 
  * @param  txd: data to be transmit 
  * @retval None 
  */  
void IIC_Send_Byte(unsigned char txd)  
{                          
	unsigned char i;     
	SDA_OUT();          
	IIC_SCL_0();//push down scl  to start transmit data   
	for(i = 0; i < 8; ++i)  
	{                
	if(txd & 0x80)  
	{  
		IIC_SDA_1();  
	}  
	else  
	{  
		IIC_SDA_0();  
	}  
	txd <<= 1;        
	delay_us(2);     
	IIC_SCL_1();  
	delay_us(2);   
	IIC_SCL_0();      
	delay_us(2);  
	}    
}       
  
/** 
  * @brief  Simulate IIC conmunication : Receive one byte Data 
  * @param  ack: Whether transmit ACK 
  * @retval the data have been receive 
  *  ack=1 send ACK
  *  ack=0 send nACK
  */    
unsigned char IIC_Read_Byte(unsigned char ack)  
{  
	unsigned char i, res = 0;  
	SDA_IN();               //SDA input mode   
	for(i = 0; i < 8; ++i ){  
		IIC_SCL_0();   
		delay_us(2);  
		IIC_SCL_1();  
		res <<= 1;  
		if(SDA_READ()){  
			res++;   
		}        
		delay_us(1);   
	}                    
	if (!ack){  
		IIC_NAck();//make NACK   
	}  
	else {  
		IIC_Ack(); //make ACK   
	}  
	return res;  
}  



void I2C_HTU21_reset(void)
{
	uint8_t tt = 0;
	IIC_Start();
	IIC_Send_Byte(HTU21D_I2CADDR);
	IIC_Wait_Ack();
	IIC_Send_Byte(HTU21D_RESET);
	IIC_Wait_Ack();  
	IIC_Stop(); 
	delay_ms(15);
	
	IIC_Start();
	IIC_Send_Byte(HTU21D_I2CADDR);
	IIC_Wait_Ack();
	IIC_Send_Byte(HTU21D_READREG);
	IIC_Wait_Ack(); 
	IIC_Stop(); 
	
	while(1)
	{
		delay_us(1);
		tt++;
		if(tt > 2) 
		{
			break;//return 0;
		}
		IIC_Start();
		IIC_Send_Byte(HTU21D_I2CADDR | 0x01);
		if (IIC_Wait_Ack())  
		{
			//delay_us(2);
			continue;  
		}
		else {
			break;
		}
	}
	tt = IIC_Read_Byte(0); 
	IIC_Stop(); 
}

//       
float I2C_TEMP_BufferRead(void)
{ 
	uint16_t tt = 0;
	uint8_t crc = 0;
	float temp=0;
	IIC_Start();
	IIC_Send_Byte(HTU21D_I2CADDR);
	IIC_Wait_Ack();  

	IIC_Send_Byte(HTU21D_READTEMP);
	IIC_Wait_Ack();  
	
	IIC_Stop(); 
	
	delay_ms(50);


	IIC_Start();
	IIC_Send_Byte(HTU21D_I2CADDR | 0x01);
	IIC_Wait_Ack();	
	
	tt = IIC_Read_Byte(1); 
	tt <<= 8;
	tt |= IIC_Read_Byte(1);
	crc = IIC_Read_Byte(0);
	IIC_Stop(); 
	
	temp = tt;
	temp *= 175.72;
	temp /= 65536;
	temp -= 46.85;
	
	return temp;
} 


float I2C_HUMI_BufferRead(void)
{ 
	uint16_t tt = 0;
	uint8_t crc = 0;
	float hum=0;
	IIC_Start();
	IIC_Send_Byte(HTU21D_I2CADDR);
	IIC_Wait_Ack();  

	IIC_Send_Byte(HTU21D_READHUMI);
	IIC_Wait_Ack();  
	
	IIC_Stop(); 
	
	delay_ms(50);


	IIC_Start();
	IIC_Send_Byte(HTU21D_I2CADDR | 0x01);
	IIC_Wait_Ack();	
	
	tt = IIC_Read_Byte(1); 
	tt <<= 8;
	tt |= IIC_Read_Byte(1);
	crc = IIC_Read_Byte(0);
	IIC_Stop(); 
	
	hum = tt;
	hum *= 125;
	hum /= 65536;
	hum -= 6;
	
	return hum;
}

void HTU21D_Func(void)
{
	//if((htu21d_temper_value > -10) && (htu21d_temper_value < 55))
	temp_value = I2C_TEMP_BufferRead();
	humi_value = I2C_HUMI_BufferRead();
	
}



