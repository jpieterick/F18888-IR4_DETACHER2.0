/** @file app_version.h
 *  @brief
 *
 *  @details
 *  To Use:
 *
 *  Assumptions made:
 *
 *
 *  @author Nick M
 *  @bug No known bugs.
 *
 *  InVue Security Products
 *  Copyright 2022
 */

/****************************************************************************/
#ifndef _APP_VERSION_H
#define _APP_VERSION_H

/****************************************************************************
						INCLUDES
*****************************************************************************/
#include <stdint.h>

//#define USING_BOBL
#ifdef USING_BOBL
#include "bootloader_logic.h"

/****************************************************************************
						GLOBAL TYPEDEFS
*****************************************************************************/
typedef union
{
    uint8_t data[SIZEOF_METADATA_WITHOUT_MAGIC_NUMBER + MAGIC_NUMBER_LENGTH];
    uint64_t for_alignment;
} bootloader_metadata_t;
#endif
/****************************************************************************
                        DEFINES AND ENUMARATED VALUES
*****************************************************************************/
#define FW_ID_LENGTH_BYTES  				8U
#define FW_START_YEAR               		2012U

/* Note: These defines are automatically created by the makefile during a build. If for some reason,
 *    you are not using the makefile then these values have to be manually set.
 *    These defines makeup the version number so it has to be set per build/release.
 */

#ifndef C_YEAR								/* Could be passed in during builds */
#define C_YEAR                       		((uint32_t)2025)
#warning "C_YEAR not defined in makefile, using default"
#endif

#ifndef C_MONTH								/* Could be passed in during builds */
#define C_MONTH                       		((uint32_t)4)
#warning "C_MONTH not defined in makefile, using default"
#endif

#ifndef C_DAY								/* Could be passed in during builds */
#define C_DAY                      			((uint32_t)29)
#warning "C_DAY not defined in makefile, using default"
#endif

#ifndef C_HOUR								/* Could be passed in during builds */
#define C_HOUR                     			((uint32_t)13)
#warning "C_HOUR not defined in makefile, using default"
#endif

#ifndef C_MIN								/* Could be passed in during builds */
#define C_MIN                     		 	((uint32_t)23)
#warning "C_MIN not defined in makefile, using default"
#endif

#ifndef FW_EXT								/* Could be passed in during builds */
#define FW_EXT                      		((uint32_t)0)
#warning "FW_EXT not defined in makefile, using default"
#endif

#ifndef FW_ID								/* FW #, 16 bit, Could be passed in during builds */
#define FW_ID								272
#warning "FW_ID not defined in makefile, using default"
#endif

#define FW_ID_MSB                   		((uint8_t)(FW_ID >> 8) )
#define FW_ID_LSB                   		((uint8_t)FW_ID)

#define FW_YR_SINCE_2000                    (C_YEAR - 2000U)
#define FW_YR_BCD_UPPER_NIBBLE              (((FW_YR_SINCE_2000) / 10U) << 4U)
#define FW_YR_BCD                           (uint8_t)((FW_YR_BCD_UPPER_NIBBLE) | (FW_YR_SINCE_2000 - (10U * (FW_YR_BCD_UPPER_NIBBLE >> 4U))))

#define FW_MO_BCD_UPPER_NIBBLE              (((C_MONTH) / 10U) << 4U)
#define FW_MO_BCD                           (uint8_t)((FW_MO_BCD_UPPER_NIBBLE) | (C_MONTH - (10U * (FW_MO_BCD_UPPER_NIBBLE >> 4U))))

#define FW_DAY_BCD_UPPER_NIBBLE             (((C_DAY) / 10U) << 4U)
#define FW_DAY_BCD                          (uint8_t)((FW_DAY_BCD_UPPER_NIBBLE) | (C_DAY - (10U * (FW_DAY_BCD_UPPER_NIBBLE >> 4U))))

#define FW_HOUR_BCD_UPPER_NIBBLE            (((C_HOUR) / 10U) << 4U)
#define FW_HOUR_BCD                         (uint8_t)((FW_HOUR_BCD_UPPER_NIBBLE) | (C_HOUR - (10U * (FW_HOUR_BCD_UPPER_NIBBLE >> 4U))))

#define FW_MIN_BCD_UPPER_NIBBLE             (((C_MIN) / 10U) << 4U)
#define FW_MIN_BCD                          (uint8_t)((FW_MIN_BCD_UPPER_NIBBLE) | (C_MIN - (10U * (FW_MIN_BCD_UPPER_NIBBLE >> 4U))))

#define FW_USER_DEFINED_BCD_UPPER_NIBBLE    (((FW_EXT) / 10U) << 4U)
#define FW_USER_DEFINED_BCD                 (uint8_t)((FW_USER_DEFINED_BCD_UPPER_NIBBLE) | (FW_EXT - (10U * (FW_USER_DEFINED_BCD_UPPER_NIBBLE >> 4U))))

/****************************************************************************
                        MACROS
*****************************************************************************/

/****************************************************************************
                        GLOBAL FUNCTION PROTOTYPES
*****************************************************************************/
#ifdef USING_BOBL
size_t our_bootloader_metadata_and_address(const uint8_t** const metadata);
size_t our_application_metadata_and_address(const uint8_t** const metadata);
size_t any_additional_application_metadata_and_address(const uint8_t** const metadata);
#endif
/****************************************************************************
                        GLOBAL VARIABLES
******************************************************************************/
extern uint8_t const invue_fw_version_new[FW_ID_LENGTH_BYTES];
extern uint16_t const invue_fw_version_legacy;

#ifdef USING_BOBL
extern volatile const __attribute__((section (".bootloader_meta_data")))bootloader_metadata_t data_for_bootloader;
#endif // USING_BOBL
#endif // _APP_VERSION_H
