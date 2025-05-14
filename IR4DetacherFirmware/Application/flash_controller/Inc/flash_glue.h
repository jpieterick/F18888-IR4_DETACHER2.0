#ifndef __FLASH_CONTROLLER_APP_H
#define __FLASH_CONTROLLER_APP_H

/****************************************************************************
						INCLUDES
*****************************************************************************/
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/***********************************************************************/
/* DEFINES                                                             */
/***********************************************************************/
#define SECURITY_KEY_SIZE                  16

/****************************************************************************
						GLOBAL TYPEDEFS
*****************************************************************************/
typedef enum /* these are the "keys" of the key/value pairs that we can store in flash */
{
  FLASH_KEY_SERIAL_NUMBER       = 1,	/*Intentionally skipping 0 */
	FLASH_KEY_SDC                 = 2,
	FLASH_KEY_IR3_MODE            = 3,
	FLASH_KEY_FACTORY_KEY         = 4,
	FLASH_KEY_FACTORY_MAC         = 5,
	FLASH_KEY_ENROLL_STATUS       = 6,
	FLASH_KEY_DELAY_SETTING       = 7,
	FLASH_KEY_IR_SETTING          = 8,
	FLASH_KEY_SDC_SET             = 9,
	FLASH_KEY_SALT                = 10,
	FLASH_ENCRYTPION_STATUS       = 11
	// ---- New Keys should be added above -----
}_tFlash_Key;

/****************************************************************************
                        DEFINES AND ENUMARATED VALUES
*****************************************************************************/
#define FLASH_KEY_NOT_FOUND	      0
#define FLASH_WRITE_ERROR			    0	 // flash_controller_write normally returns 0 on some kind of error
#define ENROLLMENT_STATUS    0x8000  // Shows if enrollment is set or not in device status.
#define SDC_STATUS           0x4000  // Shows if SDC is set or not in device status.
#define FLASH_ERROR          0x2000  // Shows that there is some sort of flash error
#define STATUS_SIZE               2

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
size_t fcul_write(_tFlash_Key flash_key, const uint8_t value[], size_t value_size);


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
size_t fcul_read(_tFlash_Key flash_key, uint8_t value[], size_t value_size);

/* Exposing some lower level functions for other translation units to directly use.
 * These functions properly disable/reenable interrupts, and pet the watchdog timer.
 */
bool fcul_is_ready( void );

/****************************************************************************
                        GLOBAL VARIABLES
******************************************************************************/

#endif /* __FLASH_CONTROLLER_APP_H */
