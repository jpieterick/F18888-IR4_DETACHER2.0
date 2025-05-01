/** @file flash_controller_app.c
 *  @brief Application layer wrapper for the flash controller module
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
#include <stdbool.h>
#include <stdlib.h>
#include <string.h> /* For memcmp and memcpy*/
#include "periphdefs.h"
#include "hal_flash.h"
#include "hal_interrupts.h"
#include "hal_watchdog.h"
#include "flash_controller_app.h"
#include "flash_controller.h"
#include "rtt_debug.h"

/****************************************************************************
                            TYPEDEFS
****************************************************************************/

/****************************************************************************
                            DEFINES
****************************************************************************/

/****************************************************************************
                            GLOBAL VARIABLES
****************************************************************************/
static flash_controller_struct fc;
static uint32_t flash_controller_initialized = 0;
extern uint8_t _NONVOLATILE_STORAGE_START; /* Defined in Linker File */
extern uint8_t _NONVOLATILE_STORAGE_END; /* Defined in Linker File */
static uint8_t fc_tempBuffer[ 16 ];

/****************************************************************************
                            FUNCTION PROTOTYPES
****************************************************************************/

/****************************************************************************
                            CODE
****************************************************************************/
/** @brief flash_write_function
 *  @details
 *  @param[in] uint8_t* destination
 *  @param[in] const uint8_t* source
 *  @param[in] unsigned int length_minus_one
 *  @return void
 */
void flash_write_function(uint8_t* destination, const uint8_t* source, unsigned int length_minus_one)
{
    hal_interrupts_disable();
    hal_watchdog_reset();
    hal_flash_write(destination, source, length_minus_one);
    hal_watchdog_reset();
    hal_interrupts_enable();
}

/** @brief flash_erase_function
 *  @details
 *  @param[in] uint8_t* start
 *  @param[in] unsigned int length_minus_one
 *  @return void
 */
void flash_erase_function(uint8_t* start, unsigned int length_minus_one)
{
    hal_interrupts_disable();
    hal_watchdog_reset();
    hal_flash_erase(start, length_minus_one);
    hal_watchdog_reset();
    hal_interrupts_enable();
}

/** @brief fcul_initialize_flash_controller
 *  @details
 *  @param[in] void
 *  @return void
 */
void fcul_initialize_flash_controller(void)
{
	fc.sector_group_length_minus_one = FLASH_SECTOR_SIZE - 1;
	fc.minimum_writeable_bytes       = FLASH_MIN_WRITE_BYTES;
	fc.bytes_per_key                 = 1;
	fc.first_sector_group_start      = (uint8_t*)&_NONVOLATILE_STORAGE_START;
	/** Once I enabled -0s build option i started to get out of bounds warning on the following code so let's ignore it. It doesn't pop up in -0g.  **/
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Warray-bounds"
	fc.second_sector_group_start     = (uint8_t*)(&_NONVOLATILE_STORAGE_START + FLASH_SECTOR_SIZE);
#pragma GCC diagnostic pop
	fc.flash_write_callback          = flash_write_function;
	fc.flash_erase_callback          = flash_erase_function;
	memset( &fc.migration, 0, sizeof( fc.migration ));
	// The two following values are part of the api change to support both internal and external memories. Remove if using an older version of the flash controller
	fc.scratchpadBuffer 			 = fc_tempBuffer;
	fc.scratchpadBufferSz 			 = sizeof(fc_tempBuffer);

	flash_controller_ensure_integrity_on_bootup(&fc);
	flash_controller_initialized = 1;
}

/** @brief fcul_write
 *  @details
 *  @param[in] _tFlash_Key key
 *  @param[in] const uint8_t *value
 *  @param[in] size_t value_size
 *  @return size_t
 */
size_t fcul_write(_tFlash_Key key, const uint8_t *value, size_t value_size)
{
    return flash_controller_write(&fc, (uint8_t*)&key, value, value_size);
}

/** @brief fcul_read
 *  @details
 *  @param[in] _tFlash_Key key
 *  @param[in] uint8_t *value
 *  @param[in] size_t value_size
 *  @return size_t
 */
size_t fcul_read(_tFlash_Key key, uint8_t *value, size_t value_size)
{
    return flash_controller_read(&fc, (uint8_t*)&key, value, value_size);
}

/** @brief fcul_is_ready
 *  @details
 *  @param[in] void
 *  @return bool
 */
bool fcul_is_ready( void )
{
	return (flash_controller_initialized > 0);
}

