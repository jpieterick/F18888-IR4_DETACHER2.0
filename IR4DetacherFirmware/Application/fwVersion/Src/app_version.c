/** @file app_version.c
 *  @brief
 *
 *  @details
 *  To Use:

 *  Assumptions made:
 *
 *
 *  @author Nick M
 *  @bug No known bugs.
 *
 *  InVue Security Products
 *  Copyright 2022
 */

/***************************************************************************
INCLUDES
****************************************************************************/
#include <stdint.h>
#include "app_version.h"
#include "hal_flash.h"
#ifdef USING_BOBL
#include "memoryMap.h"
#include "bootloader_logic.h"
#endif //

// TODO: Setup automatic firmware versioning.
/****************************************************************************
                            TYPEDEFS
****************************************************************************/
typedef enum
{
    FW_ID_NUM_MSB       = 0U,
    FW_ID_NUM_LSB,
    FW_ID_YEAR_SINCE_2000,
    FW_ID_MONTH,
    FW_ID_DAY,
    FW_ID_HOUR,
    FW_ID_MIN,
    FW_ID_EXT
}fw_version_new_enum_t;

/****************************************************************************
                            DEFINES
****************************************************************************/
// FW Compatibility
#ifndef FW_COMPATIBILITY							/* Could be passed in during builds */
#define FW_COMPATIBILITY							((uint32_t)1)
#endif
#define FW_COMPATIBILITY_MSB						((uint8_t)(FW_COMPATIBILITY >> 8) )
#define FW_COMPATIBILITY_LSB  						((uint8_t)FW_ID)

// HW Compatibility
#ifndef HW_COMPATIBILITY							/* Could be passed in during builds */
#define HW_COMPATIBILITY							((uint32_t)1)
#endif
#define HW_COMPATIBILITY_MSB						((uint8_t)(HW_COMPATIBILITY >> 8) )
#define HW_COMPATIBILITY_LSB  						((uint8_t)HW_COMPATIBILITY)

/****************************************************************************
                            GLOBAL VARIABLES
****************************************************************************/
#ifdef USING_BOBL

volatile const __attribute__((section (".bootloader_meta_data")))bootloader_metadata_t data_for_bootloader =
{
    .data =
    {
    	BMN0,       BMN1,       BMN2,       			BMN3,       			BMN4,       BMN5,       BMN6,       BMN7,               /* Magic Number part 1                                                                                                                              */
		BMN8,       BMN9,       BMN10,      			BMN11,      			BMN12,      BMN13,      BMN14,      BMN15,         		/* Magic Number part 2                                                                                                                              */
        0xFF,       0xFF,       0xFF,       			0xFF,       			0xFF,       0xFF,       0xFF,       0xFF,               /* Image invalid unless this is 0xFFFFFFFF (trailing 4 bytes are only for padding)                                                           */
		0x00, 		0xFF,       0xFF,      	 			0xFF,       			0xFF,       0xFF,       0xFF,       0xFF,               /* Image valid if this is !0xFFFFFFFF (trailing 4 bytes are only for padding)                                                           */
        0x08,       0x00,       0x80,  					0x04,       			0xFF,       0xFF,       0xFF,       0xFF,               /* Pointer to address that contains the address that the bootloader must jump to. (trailing 4 '0xFF' bytes are only for padding)                    */
        FW_ID_MSB,  FW_ID_LSB,  FW_COMPATIBILITY_MSB,  	FW_COMPATIBILITY_LSB,  	0xFF,       0xFF,       0xFF,       0xFF,               /* FW Compatibility version; includes FW ID FW00xx (0x00000000 and 0xFFFFFFFF ALWAYS compatible). (trailing 4 '0xFF' bytes are only for padding)    */
        FW_ID_MSB,  FW_ID_LSB,  FW_YR_BCD,  			FW_MO_BCD,  			FW_DAY_BCD, FW_HOUR_BCD,FW_MIN_BCD, FW_USER_DEFINED_BCD,/* Application Version.                                                                                                                        */
        FW_ID_MSB,  FW_ID_LSB,  HW_COMPATIBILITY_MSB,  	HW_COMPATIBILITY_LSB,  	0xFF,       0xFF,       0xFF,       0xFF,               /* Hardware Compatibility Number.  Use FW ID. (trailing 4 '0xFF' bytes are only for padding)                                                        */
        0x00,       0x00,       0x00,       			0x00,       			0xFF,       0xFF,       0xFF,       0xFF,               /* Pointer to 8 byte Serial Number.                                                                                                                 */
    }
};
#endif
uint8_t const invue_fw_version_new[FW_ID_LENGTH_BYTES] = 
{
    FW_ID_MSB,
    FW_ID_LSB,
    FW_YR_BCD,
    FW_MO_BCD,
    FW_DAY_BCD,
    FW_HOUR_BCD,
    FW_MIN_BCD,
    FW_USER_DEFINED_BCD
};

uint16_t const invue_fw_version_legacy = ((C_YEAR - FW_START_YEAR) << 12U) | (C_MONTH << 8U) | (C_DAY << 3U) | FW_EXT;

/****************************************************************************
                            FUNCTION PROTOTYPES
****************************************************************************/
#ifdef USING_BOBL
size_t our_bootloader_metadata_and_address(const uint8_t** const metadata)
{
    return bootloader_logic_get_metadata_address(metadata, ( const uint8_t*)data_for_bootloader.data, hal_flash_get_lowest_bootloader_address(), hal_flash_get_highest_bootloader_address());
}

size_t our_application_metadata_and_address(const uint8_t** const metadata)
{
    *metadata = (const uint8_t*)&data_for_bootloader.data[MAGIC_NUMBER_LENGTH];
    return SIZEOF_METADATA_WITHOUT_MAGIC_NUMBER;
}

/* if there is a 2nd application somewhere on this chip besides us */
size_t any_additional_application_metadata_and_address(const uint8_t** const metadata)
{
    return bootloader_logic_get_metadata_address(metadata, (const uint8_t*)data_for_bootloader.data, hal_flash_get_highest_bootloader_address(), (const uint8_t*)hal_flash_get_end_address());
}
#endif
