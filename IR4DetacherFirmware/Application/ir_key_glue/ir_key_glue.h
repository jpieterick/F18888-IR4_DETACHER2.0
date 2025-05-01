/** @file ir_key_glue.h
 *  @brief Simple wrapper for IR related Comms
 *
 *  @details
 *  To Use:
 *
 *  Assumptions mode:
 *
 *
 *  @author Nick M
 *  @bug No known bugs.
 *
 *  InVue Security Products
 *  Copyright 2024
 */
#ifndef IR_KEY_GLUE_H_
#define IR_KEY_GLUE_H_

/****************************************************************************
            			INCLUDES
*****************************************************************************/
#include <stdint.h> /* needed for uint8_t, uint16_t, etc. */ 
#include <stddef.h> /* needed for size_t */
#include <stdbool.h>
#include "periphdefs.h"
#include "invue_ir_comms.h"

/****************************************************************************
            			GLOBAL TYPEDEFS
*****************************************************************************/

/****************************************************************************
						MACROS
*****************************************************************************/

/****************************************************************************
                        DEFINES AND ENUMARATED VALUES
*****************************************************************************/

/****************************************************************************
                        GLOBAL FUNCTION PROTOTYPES
*****************************************************************************/
bool factory_reset(void);
void irKey_diff_serial_and_update( uint8_t *_sn );
void irkey_gl_init(enum uart_id UART_IR_KEY);
bool irkey_gl_is_inactive(void);
void irkey_gl_key_handler(void);
void irKey_gl_HandleTimers( uint32_t elapsed_ms );
void irkey_gl_setIRKeyCommsEnabled( void );
uint32_t irkey_gl_getRxbyte( uint8_t *p_ReceivedByte );
void irkey_gl_addTxByte( const uint8_t *p_TransmitByte );
void irkey_gl_switchHWToKeyComms( void );
void irkey_gl_trigger_transmit( void );
void set_ir_for_sleep( void );
void set_ir_for_active( void );
bool irKey_runLoopback( void )__attribute__ ((optimize("-O0")));
void irKey_reset_sdc(void);
void irKey_reset_mode(void);
bool is_my_serial_valid( void );
bool is_ir_mode_IR1( void );
bool irKey_have_valid_SDC( void );
bool single_ir_keypress_detected( void );
bool irKey_has_authorized_key_been_used_first_time( void );
void flash_debug(void); //TODO Remove
void ir_rx_gpio_cb( uint32_t intNum );
void wireless_power_detected(void);

#endif /* IR_KEY_GLUE_H_ */
