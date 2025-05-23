/** @file nvm_interface.c
 *  @brief This is a middle layer between the application and what ever NVM module being used (flash controller or nv_data_controller or other).
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
#include <string.h> /* For memcmp and memcpy*/
#include "flash_controller_app.h"
#include "nvm_interface.h"
#include "invue_ir_comms.h"

/****************************************************************************
                            TYPEDEFS
****************************************************************************/

/****************************************************************************
                            DEFINES
****************************************************************************/

/****************************************************************************
                            GLOBAL VARIABLES
****************************************************************************/

/****************************************************************************
                            FUNCTION PROTOTYPES
****************************************************************************/

/****************************************************************************
                            CODE
****************************************************************************/
/** @brief nvm_read_sdc
 *  @details
 *  @param[in] uint8_t *ptr
 *  @param[in] uint32_t length
 *  @return uint32_t: Bytes copied or 0 if not found
 */
uint32_t nvm_read_sdc( uint8_t *ptr, uint32_t length )
{
	if( fcul_read( FLASH_KEY_SDC, ptr, length) == FLASH_KEY_NOT_FOUND )
	{
		return 0;
	}
	return length;
}

/** @brief nvm_write_sdc
 *  @details
 *  @param[in] uint8_t *ptr
 *  @param[in] uint32_t length
 *  @return uint32_t
 */
uint32_t nvm_write_sdc( uint8_t *ptr, uint32_t length )
{
	return ( fcul_write( FLASH_KEY_SDC, (const uint8_t*)ptr, length) );
}

/** @brief nvm_read_serial
 *  @details
 *  @param[in] uint8_t *ptr
 *  @param[in] uint32_t length
 *  @return uint32_t
 */
uint32_t nvm_read_serial( uint8_t *ptr, uint32_t length )
{
	if( fcul_read( FLASH_KEY_SERIAL_NUMBER, ptr, length) == FLASH_KEY_NOT_FOUND )
	{
		return 0;
	}
	return length;
}

/** @brief nvm_write_serial
 *  @details
 *  @param[in] uint8_t *ptr
 *  @param[in] uint32_t length
 *  @return uint32_t
 */
uint32_t nvm_write_serial( uint8_t *ptr, uint32_t length )
{
	return ( fcul_write( FLASH_KEY_SERIAL_NUMBER, (const uint8_t*)ptr, length) );
}

/** @brief nvm_read_ir_mode
 *  @details
 *  @param[in] uint8_t *ptr
 *  @param[in] uint32_t length
 *  @return uint32_t
 */
uint32_t nvm_read_ir_mode( uint8_t *ptr, uint32_t length )
{
	if( fcul_read( FLASH_KEY_IR3_MODE, ptr, length) == FLASH_KEY_NOT_FOUND )
	{
		return 0;
	}
	return length;
}

/** @brief nvm_write_ir_mode
 *  @details
 *  @param[in] uint8_t *ptr
 *  @param[in] uint32_t length
 *  @return uint32_t
 */
uint32_t nvm_write_ir_mode( uint8_t *ptr, uint32_t length )
{
	return ( fcul_write( FLASH_KEY_IR3_MODE, (const uint8_t*)ptr, length) );
}

/** @brief nvm_write_security_state
 *  @details
 *  @param[in] uint8_t *ptr
 *  @param[in] uint32_t length
 *  @return uint32_t
 */
uint32_t nvm_write_security_state( uint8_t *ptr, uint32_t length )
{
	return ( fcul_write( FLASH_KEY_SPURIOUS_RESET_DATA, (const uint8_t*)ptr, length) );
}

/** @brief nvm_read_security_state
 *  @details
 *  @param[in] uint8_t *ptr
 *  @param[in] uint32_t length
 *  @return uint32_t
 */
uint32_t nvm_read_security_state( uint8_t *ptr, uint32_t length )
{
	if( fcul_read( FLASH_KEY_SPURIOUS_RESET_DATA, ptr, length) == FLASH_KEY_NOT_FOUND )
	{
		return 0;
	}
	return length;
}

/** @brief nvm_reset_to_defaults
 *  @details
 *  @param[in] void
 *  @return bool: success if true
 */
bool nvm_reset_to_defaults( void )
{
	uint8_t nvm[DEVICE_SN_BYTES] = {0};
	bool writeSuccess = true;

	// Using the flash controller so we cannot erase records, just update all

	// Reset IR SDC to 0,0,0,0
	writeSuccess &= (nvm_write_sdc( nvm, SZ_OF_IR3_SDC) == SZ_OF_IR3_SDC);

	// Reset Serial # to 00 00 00 00 00 00 00 00
	writeSuccess &= (nvm_write_serial( nvm, DEVICE_SN_BYTES) == DEVICE_SN_BYTES);

	// Reset IR Mode to 0
	writeSuccess &= (nvm_write_ir_mode( nvm, 1) == 1);

	// Reset security state to 0
	writeSuccess &= (nvm_write_security_state( nvm, 4) == 4);

	// Reset Lockdown state to 0 (unlocked)
	writeSuccess &= (nvm_write_lockdown_position( nvm, 1) == 1);

	return writeSuccess;
}

/** @brief nvm_read_lockdown_position
 *  @details
 *  @param[in] uint8_t *ptr
 *  @param[in] uint32_t length
 *  @return uint32_t
 */
uint32_t nvm_read_lockdown_position( uint8_t *ptr, uint32_t length )
{
	if( fcul_read( FLASH_KEY_LOCKDOWN_STATE, ptr, length) == FLASH_KEY_NOT_FOUND )
	{
		return 0;
	}
	return length;
}

/** @brief nvm_write_lockdown_position
 *  @details
 *  @param[in] uint8_t *ptr
 *  @param[in] uint32_t length
 *  @return uint32_t
 */
uint32_t nvm_write_lockdown_position( uint8_t *ptr, uint32_t length )
{
	return ( fcul_write( FLASH_KEY_LOCKDOWN_STATE, (const uint8_t*)ptr, length) );
}
