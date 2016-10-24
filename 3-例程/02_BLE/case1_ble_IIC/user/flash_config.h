#ifndef __FLASH_CONFIG_H__
#define __FLASH_CONFIG_H__
#include "nordic_common.h"
#include "nrf.h"

/* this is page config for ozner's skin */
#define PAGE_NUM_FOR_DATA                 (32)
#define PAGE_NUM_FOR_SWAP                 (60)
#define PAGE_NUM_FOR_CONFIG               (10)

#define OTA_BLOCK_START_PAGE              (NRF_FICR->CODESIZE-14)
#define CONFIG_BLOCK_START_PAGE           (NRF_FICR->CODESIZE-24)
#define DATA_BLOCK_START_PAGE             (NRF_FICR->CODESIZE-56)
#define SWAP_BLOCK_STAET_PAGE             (NRF_FICR->CODESIZE-116)

#define ERASABLE_BLOCK_START              (DATA_BLOCK_START_PAGE)
#define ERASABLE_BLOCK_END                (CONFIG_BLOCK_START_PAGE + PAGE_NUM_FOR_CONFIG)

#define FLASH_PAGE_STORE_TIME             (NRF_FICR->CODESIZE-23)                           /**< used to store */
#define FLASH_PAGE_DAILY_TARGET           (NRF_FICR->CODESIZE-22)           /**< Flash page used for SN and factory test flag*/
//#define FLASH_PAGE_ERROR_LOG              (NRF_FICR->CODESIZE-21)                           /**< Address in flash where stack trace can be stored. */
#define FLASH_PAGE_SYS_ATTR               (NRF_FICR->CODESIZE-20)                           /**< Flash page used for bond manager system attribute information. */
#define FLASH_PAGE_BOND                   (NRF_FICR->CODESIZE-19)                           /**< 232 Flash page used for bond manager bonding information. */
#define FLASH_PAGE_PRIVATE_BOND           (NRF_FICR->CODESIZE-18)
#define FLASH_PAGE_USER_PROFILE           (NRF_FICR->CODESIZE-17)           /**< Flash page used for user profile*/
#define FLASH_PAGE_ALARM_SETTINGS         (NRF_FICR->CODESIZE-16)           /**< Flash page used for alarm settings*/
#define FLASH_PAGE_SN_FACTORY_FLAG        (NRF_FICR->CODESIZE-15)           /**< Flash page used for SN and factory test flag*/

#define FLASH_PAGE_HEALTH_DATA             DATA_BLOCK_START_PAGE                             /**< start page used to store sports data > */
#define FLASH_PAGE_SLEEP_SETTINGS         (NRF_FICR->CODESIZE-25)                           /**< used to store sleep setting data*/

#define FLASH_PAGE_SIZE                   (NRF_FICR->CODEPAGESIZE)




#endif



