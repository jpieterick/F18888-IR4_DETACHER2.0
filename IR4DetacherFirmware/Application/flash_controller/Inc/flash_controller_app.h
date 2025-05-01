/** @file flash_controller_app.h
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
#ifndef __FLASH_CONTROLLER_APP_H
#define __FLASH_CONTROLLER_APP_H

/****************************************************************************
						INCLUDES
*****************************************************************************/
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/****************************************************************************
						GLOBAL TYPEDEFS
*****************************************************************************/
typedef enum
{
    FLASH_KEY_SDC                             = 1,	/*Intentionally skipping 0 */
    FLASH_KEY_IR3_MODE                        = 2,
    FLASH_KEY_SERIAL_NUMBER                   = 3,
    FLASH_KEY_SPURIOUS_RESET_DATA             = 4, /* store if we're armed or alarming, so security is maintained across spurious resets */
    FLASH_KEY_RESET_COUNTER                   = 5,
	FLASH_KEY_LOCKDOWN_STATE				  = 6
}_tFlash_Key /* these are the "keys" of the key/value pairs that we can store in flash */;

/****************************************************************************
                        DEFINES AND ENUMARATED VALUES
*****************************************************************************/
#define FLASH_KEY_NOT_FOUND						0

/****************************************************************************
                        MACROS
*****************************************************************************/

/****************************************************************************
                        GLOBAL FUNCTION PROTOTYPES
*****************************************************************************/
void fcul_initialize_flash_controller(void);

/* Copies a value_size number of bytes pointed to by value into flash.
 *
 * Returns the number of bytes copied (max 255).
 * Returns 0 if there is some kind of error.
 * TODO: meaningfully implement the return value.
 *
 * Note that this function calls flash_write_callback(), and will also call 
 * flash_erase_callback() if a migration (from one sector group to another) is 
 * triggered due to a lack of space in the active sector group.
 */
size_t fcul_write(_tFlash_Key flash_key, const uint8_t *value, size_t value_size);



/* Finds the data associated with key, and copies it into value.  The number of 
 * bytes copied will either be value_size or the number of bytes that are 
 * actually stored, whichever is smaller.
 *
 * Note that this function COPIES data to an address specified by the caller 
 * instead of RETURNING the address in flash at which the desired data already 
 * exists.  This design decision is on purpose, because such a returned address 
 * might point to invalid data if a subsequent write causes a migration.
 *
 * Returns the number of bytes copied (max 255).
 * Returns 0 if the key was not found.
 *
 * Never calls flash_write_callback() or flash_erase_callback().
 */
size_t fcul_read(_tFlash_Key flash_key, uint8_t *value, size_t value_size);

/* Exposing some lower level functions for other translation units to directly use.
 * These functions properly disable/reenable interrupts, and pet the watchdog timer.
 */
bool fcul_is_ready( void );

void flash_write_function(uint8_t* destination, const uint8_t* source, unsigned int length_minus_one);
void flash_erase_function(uint8_t* start, unsigned int length_minus_one);
/****************************************************************************
                        GLOBAL VARIABLES
******************************************************************************/

#endif /* __FLASH_CONTROLLER_APP_H */

















