/** @file nvm_interface.h
 *  @brief  *  @brief This is a middle layer between the application and what ever NVM module being used (flash controller or nv_data_controller or other).
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
#ifndef __NVM_INTERFACE_H
#define __NVM_INTERFACE_H

/****************************************************************************
							INCLUDES
*****************************************************************************/
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

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
uint32_t nvm_read_sdc( uint8_t *ptr, uint32_t length );
uint32_t nvm_write_sdc( uint8_t *ptr, uint32_t length );
uint32_t nvm_read_serial( uint8_t *ptr, uint32_t length );
uint32_t nvm_write_serial( uint8_t *ptr, uint32_t length );
uint32_t nvm_read_ir_mode( uint8_t *ptr, uint32_t length );
uint32_t nvm_write_ir_mode( uint8_t *ptr, uint32_t length );
uint32_t nvm_write_security_state( uint8_t *ptr, uint32_t length );
uint32_t nvm_read_security_state( uint8_t *ptr, uint32_t length );
bool nvm_reset_to_defaults( void );
uint32_t nvm_read_lockdown_position( uint8_t *ptr, uint32_t length );
uint32_t nvm_write_lockdown_position( uint8_t *ptr, uint32_t length );

#endif /* __NVM_INTERFACE_H */
