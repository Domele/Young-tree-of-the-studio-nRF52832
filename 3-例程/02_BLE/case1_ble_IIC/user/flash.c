#include "flash.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "bootloader_util.h"
#include <stdint.h>
#include "nordic_common.h"
#include "bootloader_types.h"
#include "dfu_types.h"
#include "ble_flash.h"
#include "delay.h"
#include "nrf_soc.h"
#include "nrf_sdm.h"
#include "nrf51.h"
#include "pca10001.h"
#include "crc16.h"
//sd_flash_write(uint32_t * const p_dst, uint32_t const * const p_src, uint32_t size));
//sd_flash_page_erase(uint32_t page_number));

static uint32_t               m_image_size;
static uint32_t               m_image_crc;
//static uint32_t               p_size;
//static uint32_t               p_checksum;

uint32_t sd_flash_read(uint32_t * p_dst_address, uint32_t * p_src_address,uint16_t * p_word_count)
{
    int byte_count;
	byte_count = (*p_word_count) * sizeof(uint32_t);
	memcpy(p_dst_address,p_src_address,byte_count);
	return NRF_SUCCESS;
}

uint32_t ble_flash_block_read(uint32_t * p_address, uint32_t * p_in_array, uint16_t word_count)
{
    uint16_t i;
    
    for (i = 0; i < word_count; i++)
    {
		sd_flash_read(p_in_array,p_address,&word_count);
        p_address++;
    }

    return NRF_SUCCESS;
}

uint32_t app_flash_erase(void)
{
    uint32_t              page_count;
    uint32_t              err_code;
    
    // Clear swap area.
    uint32_t   flash_page_size      = NRF_FICR->CODEPAGESIZE;
    // Erase swap.
    uint32_t * p_bank_start_address = (uint32_t *)APPL_FLASH_START_PAGE; 
    
    uint32_t page         = APPL_FLASH_START_PAGE / flash_page_size;
    uint32_t num_of_pages = APPL_FLASH_SIZE_PAGE / flash_page_size;  
           
    if (*p_bank_start_address != EMPTY_FLASH_MASK){
        for (page_count = 0; page_count < num_of_pages; page_count++)
        {
            err_code = ble_flash_page_erase(page + page_count);//sd_flash_page_erase
            if (err_code != NRF_SUCCESS)
            {
                
                return err_code;
            }
        }
	}
    return NRF_SUCCESS;
}

uint32_t swap_flash_erase(void)
{
    uint32_t              page_count;
    uint32_t              err_code;
    
    // Clear swap area.
    uint32_t   flash_page_size      = NRF_FICR->CODEPAGESIZE;
    // Erase swap.
    uint32_t * p_bank_start_address = (uint32_t *)SWAP_FLASH_START_PAGE; 
    
    uint32_t page         = SWAP_FLASH_START_PAGE / flash_page_size;
    uint32_t num_of_pages = SWAP_FLASH_SIZE_PAGE / flash_page_size;  
           
    if (*p_bank_start_address != EMPTY_FLASH_MASK){
        for (page_count = 0; page_count < num_of_pages; page_count++)
        {
            err_code = sd_flash_page_erase(page + page_count);
			//err_code = ble_flash_page_erase(page + page_count);
            APP_ERROR_CHECK(err_code);
			nrf_gpio_pin_toggle(LED_R);
			delay_ms(60);
        }
	}
    return NRF_SUCCESS;
}

/*
uint8_t flag[4];
uint32_t  sdfu_flag_addr = SDFU_FLAG_ADDR_PAGE*FLASH_PAGE_SIZE;
// Get the flag of sdfu from the flash
flag[0] = *(uint8_t *)(sdfu_flag_addr+0);
flag[1] = *(uint8_t *)(sdfu_flag_addr+1);
flag[2] = *(uint8_t *)(sdfu_flag_addr+2);
flag[3] = *(uint8_t *)(sdfu_flag_addr+3);
*/

uint32_t crc16_sum(const uint32_t * p_data, uint32_t size, const uint32_t * p_crc)
{
    uint32_t i;
	uint32_t checksum=0;
	unsigned long TempMask=0xFFFFFFFFL;
    unsigned long crc = (p_crc == NULL) ? 0x0000 : *p_crc;
	size=size/4;
    for (i = 0; i < size; i++)
    {
        crc +=  p_data[i];
    }
    checksum = (uint32_t)(crc&TempMask);
    return checksum;
}

uint32_t copy_from_swap_flash_to_app_flash(void)
{
	uint32_t  err_code;
	uint32_t            num_of_words;
	uint32_t            flash_page_size;
	uint32_t            page_start;
	uint32_t            num_of_pages;
	uint32_t            page_count;
	uint32_t *          p_bank_0_start_address;
	uint32_t *          p_bank_1_start_address;    

	uint8_t      active_image_times_count = 0;
	uint32_t     p_crc;
	
//	union tmp_str {
//	uint32_t int_string[10];
//	uint8_t char_string[20];
//	};

//	union tmp_str tmp_buf_str;
//	uint16_t buf_str_count=4;

	flash_page_size        = NRF_FICR->CODEPAGESIZE;

	
	/* backup_app_flash_to_appl0_flash */
	p_bank_0_start_address = (uint32_t *)APPL0_FLASH_START_PAGE;
	p_bank_1_start_address = (uint32_t *)APPL_FLASH_START_PAGE;
	page_start             = APPL0_FLASH_START_PAGE / flash_page_size;
	num_of_pages           = APPL0_FLASH_SIZE_PAGE  / flash_page_size;
	active_image_times_count=0;
	m_image_size=APPL_FLASH_SIZE_PAGE;
	m_image_crc  = crc16_compute((uint8_t*)APPL_FLASH_START_PAGE,
	                                 m_image_size, 
									 NULL);
									 
	while(active_image_times_count < ACTIVE_IMAGE_TRY_TIMES) {//try 2 timers
		// Erase BANK 0.
		for (page_count = 0; page_count < num_of_pages; page_count++)
		{
			err_code = ble_flash_page_erase(page_start + page_count);
			if (err_code != NRF_SUCCESS)
			{
				return err_code;
			}
			nrf_gpio_pin_toggle(LED_B);
			delay_ms(5);
		}
		nrf_gpio_pin_toggle(LED_R);
		delay_ms(50);
		// Copying bytes from BANK 1  to BANK 0.
		num_of_words = m_image_size / sizeof(uint32_t);
		err_code     = ble_flash_block_write(p_bank_0_start_address, 
											 p_bank_1_start_address, 
											 num_of_words);
		nrf_gpio_pin_toggle(LED_R);
		p_crc  = crc16_compute((uint8_t*)APPL0_FLASH_START_PAGE,
	                                 m_image_size, 
									 NULL);
		
		//p_crc = m_image_crc;
		if (m_image_crc != p_crc) {
			active_image_times_count++;
		}
		else {
			break;
		}
	}
	if(active_image_times_count>ACTIVE_IMAGE_TRY_TIMES-1) return NRF_SUCCESS;
	
	/* copy_from_swap_flash_to_app_flash */
    p_bank_0_start_address = (uint32_t *)APPL_FLASH_START_PAGE;
	p_bank_1_start_address = (uint32_t *)SWAP_FLASH_START_PAGE;
	page_start             = APPL_FLASH_START_PAGE / flash_page_size;
	num_of_pages           = APPL_FLASH_SIZE_PAGE  / flash_page_size;
	active_image_times_count=0;
	m_image_size=APPL_FLASH_SIZE_PAGE;
	m_image_crc  = crc16_compute((uint8_t*)SWAP_FLASH_START_PAGE,
	                                 m_image_size, 
									 NULL);
									 
	while(active_image_times_count < ACTIVE_IMAGE_TRY_TIMES) {//try 2 timers
		// Erase BANK 0.
		for (page_count = 0; page_count < num_of_pages; page_count++)
		{
			err_code = ble_flash_page_erase(page_start + page_count);
			if (err_code != NRF_SUCCESS)
			{
				return err_code;
			}
			nrf_gpio_pin_toggle(LED_G);
			delay_ms(5);
		}
		nrf_gpio_pin_toggle(LED_R);
		delay_ms(50);
		// Copying bytes from BANK 1  to BANK 0.
		num_of_words = m_image_size / sizeof(uint32_t);
		err_code     = ble_flash_block_write(p_bank_0_start_address, 
											 p_bank_1_start_address, 
											 num_of_words);
		nrf_gpio_pin_toggle(LED_R);
		p_crc  = crc16_compute((uint8_t*)APPL_FLASH_START_PAGE,
	                                 m_image_size, 
									 NULL);
		
		//p_crc = m_image_crc;
		if (m_image_crc != p_crc) {
			active_image_times_count++;
		}
		else {
			break;
		}
	}
	
	/* 升级错误处理 */
	if(active_image_times_count>ACTIVE_IMAGE_TRY_TIMES-1){
		/*
		恢复之前备份的app
		*/
		/* backup_app_flash_to_appl0_flash */
		p_bank_0_start_address = (uint32_t *)APPL_FLASH_START_PAGE;
		p_bank_1_start_address = (uint32_t *)APPL0_FLASH_START_PAGE;
		page_start             = APPL_FLASH_START_PAGE / flash_page_size;
		num_of_pages           = APPL_FLASH_SIZE_PAGE  / flash_page_size;
		active_image_times_count=0;
		m_image_size=APPL0_FLASH_SIZE_PAGE;
		m_image_crc  = crc16_compute((uint8_t*)APPL0_FLASH_START_PAGE,
										 m_image_size, 
										 NULL);
										 
		while(active_image_times_count < ACTIVE_IMAGE_TRY_TIMES) {//try 2 timers
			// Erase BANK 0.
			for (page_count = 0; page_count < num_of_pages; page_count++)
			{
				err_code = ble_flash_page_erase(page_start + page_count);
				if (err_code != NRF_SUCCESS)
				{
					return err_code;
				}
				nrf_gpio_pin_toggle(LED_B);
				delay_ms(5);
			}
			nrf_gpio_pin_toggle(LED_R);
			delay_ms(50);
			// Copying bytes from BANK 1  to BANK 0.
			num_of_words = m_image_size / sizeof(uint32_t);
			err_code     = ble_flash_block_write(p_bank_0_start_address, 
												 p_bank_1_start_address, 
												 num_of_words);
			nrf_gpio_pin_toggle(LED_R);
			p_crc  = crc16_compute((uint8_t*)APPL_FLASH_START_PAGE,
										 m_image_size, 
										 NULL);
			
			//p_crc = m_image_crc;
			if (m_image_crc != p_crc) {
				active_image_times_count++;
			}
			else {
				break;
			}
		}
		
	}
	//if(active_image_times_count>ACTIVE_IMAGE_TRY_TIMES-1) return NRF_SUCCESS;	
	
	return NRF_SUCCESS;

}

uint8_t read_ota_upgrade_status(void)
{
//    uint32_t ota_static_flag_address=DATA_FLASH_START_PAGE;
//	uint32_t ota_static_flag_array;
//	uint16_t ota_static_flag_count=1;
//	/*
//	判断是否进入update
//	=1 goto update
//	*/
//    sd_flash_read(&ota_static_flag_array,&ota_static_flag_address,&ota_static_flag_count);
//	if(ota_static_flag_array==DATA_FLASH_MAGIC){
//		return 1;
//	}
//	else {
//		return 0;
//	}
	
	uint32_t * ota_static_flag_address=(uint32_t * )DATA_FLASH_START_PAGE;
	uint32_t ota_static_flag_array;
	uint16_t ota_static_flag_count=1;
	/*
	判断是否进入update
	=1 goto update
	*/
    sd_flash_read(&ota_static_flag_array,ota_static_flag_address,&ota_static_flag_count);
	if(ota_static_flag_array==DATA_FLASH_MAGIC){
		return 1;
	}
	else {
		return 0;
	}
}



void write_ota_upgrade_status(uint32_t ota_static_flag_array)
{
//    uint32_t  err_code;
//	uint32_t * ota_static_flag_address=(uint32_t * )DATA_FLASH_START_PAGE;

//    err_code = sd_flash_write(ota_static_flag_address,&ota_static_flag_array,1);
//    APP_ERROR_CHECK(err_code);
//	delay_ms(20);
//	//return ;
	
	uint32_t  err_code;
	uint32_t * ota_static_flag_address = (uint32_t * )DATA_FLASH_START_PAGE;
    uint32_t  ota_static_array = ota_static_flag_array;
    err_code = ble_flash_block_write(ota_static_flag_address,&ota_static_array,1);
    APP_ERROR_CHECK(err_code);
	delay_ms(20);
	//return ;
	
	
	
}


/**@brief Function for disabling all interrupts before jumping from bootloader to application.
 */
static void interrupts_disable(void)
{
    uint32_t interrupt_setting_mask;
    uint8_t  irq;

    // We start the loop from first interrupt, i.e. interrupt 0.
    irq                    = 0;
    // Fetch the current interrupt settings.
    interrupt_setting_mask = NVIC->ISER[0];
    
    for (; irq < MAX_NUMBER_INTERRUPTS; irq++)
    {
        if (interrupt_setting_mask & (IRQ_ENABLED << irq))
        {
            // The interrupt was enabled, and hence disable it.
            NVIC_DisableIRQ((IRQn_Type) irq);
        }
    }        
}


__asm void StartApplication(uint32_t start_addr)
{
    LDR   R2, [R0]               ; //Get App MSP.
    MSR   MSP, R2                ; //Set the main stack pointer to the applications MSP.
    LDR   R3, [R0, #0x00000004]  ; //Get application reset vector address.
    BX    R3                     ; //No return - stack code is now activated only through SVC and plain interrupts.
    ALIGN
}


void StartApplication_start(uint32_t start_addr)
{
    StartApplication(start_addr);
}

void bootloader_to_app_start(uint32_t app_addr)
{
    uint32_t err_code;
	// If the applications CRC has been checked and passed, the magic number will be written and we
    // can start the application safely.
 //   err_code = sd_softdevice_disable();
 //   APP_ERROR_CHECK(err_code);
    //set retain register
	NRF_POWER->GPREGRET = 0x00;
	//clear AIRCR register
	NRF_POWER->RESETREAS = 0x04;
	
    interrupts_disable();

    err_code = sd_softdevice_forward_to_application();
    APP_ERROR_CHECK(err_code);

    StartApplication_start(app_addr);
}

void app_to_bootloader_start(uint32_t app_addr)
{
    uint32_t err_code;
	// If the applications CRC has been checked and passed, the magic number will be written and we
    // can start the application safely.
    err_code = sd_softdevice_disable();
    APP_ERROR_CHECK(err_code);
	
    //set retain register
	NRF_POWER->GPREGRET = 0x00;
	//clear AIRCR register
	NRF_POWER->RESETREAS = 0x04;
	
    interrupts_disable();
	
//	err_code = sd_softdevice_forward_to_application();
//    APP_ERROR_CHECK(err_code);

    StartApplication_start(app_addr);
}



