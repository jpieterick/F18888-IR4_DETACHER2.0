/*
 * invue_NFC.h
 *
 *  Created on: Jul 19, 2024
 *      Author: mwarren
 *
 *  InVue Security Products
 *  Copyright 2024
 */

#ifndef APPLICATION_INVUE_NFC_H_
#define APPLICATION_INVUE_NFC_H_


/***********************************************************************/
/* INCLUDES                                                            */
/***********************************************************************/
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#include "ntagInterfaceDriver.h"



/***********************************************************************/
/* DEFINES                                                             */
/***********************************************************************/



/***********************************************************************/
/* TYPES                                                               */
/***********************************************************************/
typedef enum
{
  NFC_IDLE = 0,
  NFC_DETECTED,
  NFC_GET_INFO,
  NFC_UNLOCK,
  NFC_READ_ENROLLMENT,
  NFC_FUOTA,
  NFC_LAST
} nfc_status_e;


/***********************************************************************/
/* GLOBAL VARIABLES                                                    */
/***********************************************************************/
extern volatile bool nfc_detected_flag;

/***********************************************************************/
/* GLOBAL FUNCTION PROTOTYPES                                          */
/***********************************************************************/
void set_Device_Status(uint16_t status);
void clear_Device_Status(uint16_t status);
void generic_debug(const char * pcFormat, ...);
void nfc_int_callback( uint32_t intNum );
void vout_int_callback( uint32_t intNum);
nfc_status_e application_get_state_for_NFC(void);
void nfc_comms_handler(ntagInterfaceHndl_t* ntag);
bool is_rf_field_active( void );
void clear_NFC_unlock(void);
bool nfc_unlock_detected( void );
bool nfc_is_interrupt_active( void );
bool did_rf_field_just_change( void );
void nfc_comms_HandleTimers( uint32_t elapsed_ms );
void init_get_info(void);
void nfc_clear_rw_access(NTAG_device_hndl_t *devHandle);
#endif /* APPLICATION_INVUE_NFC_H_ */
