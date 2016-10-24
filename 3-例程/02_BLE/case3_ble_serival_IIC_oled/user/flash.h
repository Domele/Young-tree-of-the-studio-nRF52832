#ifndef __FLASH_H__
#define __FLASH_H__

#include <stdint.h>
#include "nordic_common.h"


#define APPL_FLASH_START_PAGE  0x14000 
#define APPL_FLASH_SIZE_PAGE   0xc800
//0x14000   0x20800 50k app_now

#define SWAP_FLASH_START_PAGE  0x20800 
#define SWAP_FLASH_SIZE_PAGE   0xc800 
//0x20800   0x2D000 50k app_swap

#define APPL0_FLASH_START_PAGE  0x2D000 
#define APPL0_FLASH_SIZE_PAGE   0xc800 
//0x2D000   0x39800 50k app_old

#define DATA_FLASH_START_PAGE  0x39800 
//0x39800   0x3c900 1k  image_size_checksum_data

#define SN_FLASH_START_PAGE    0x3c900
//0x3c900   0x3a000 1k  SN

#define BOOT_FLASH_START_PAGE  0x3a000 
//0x3a000   0x40000 24k bootloader 

#define DATA_FLASH_MAGIC 0x5a5a

#define ACTIVE_IMAGE_TRY_TIMES      (3)

#define IRQ_ENABLED             0x01                    /**< Field identifying if an interrupt is enabled. */
#define MAX_NUMBER_INTERRUPTS   32                      /**< Maximum number of interrupts available. */

uint32_t sd_flash_read(uint32_t * p_dst_address, uint32_t * p_src_address,uint16_t * p_word_count);
uint32_t ble_flash_block_read(uint32_t * p_address, uint32_t * p_in_array, uint16_t word_count);

//void my_interrupts_disable(void);

uint32_t app_flash_erase(void);
uint32_t swap_flash_erase(void);
uint32_t copy_from_swap_flash_to_app_flash(void);
uint32_t crc16_sum(const uint32_t * p_data, uint32_t size, const uint32_t * p_crc);
uint8_t read_ota_upgrade_status(void);
void write_ota_upgrade_status(uint32_t ota_static_flag_array);
void bootloader_to_app_start(uint32_t app_addr);
void app_to_bootloader_start(uint32_t app_addr);


#endif

