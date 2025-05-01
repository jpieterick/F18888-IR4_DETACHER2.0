//****************************************************************
//  Copyright 2015 InVue Security Products, Charlotte, NC
//
//  File: invue_ir_key_app.h
//
//  Description: Header for IR Key functions
//
//  Author(s): kburtness
//
//****************************************************************

#ifndef INVUE_IR_KEY_APP_H_
#define INVUE_IR_KEY_APP_H_

#include <stdint.h>
#include <stdbool.h>
#include "invue_ir_comms.h"



// There are multiple consumers of certain data, but the consumer destroys the 
// data upon read, therefore the implementation stores one copy of the data per 
// consumer.  This enumeration specifies which copy to use.  Each consumer must 
// use its own enumeration and no others.  The first and last enumerations are 
// so the implementation can iterate over all the consumers.
enum ir_key_data_recipient_id
{
    IR_DATA_FIRST_RECIPIENT_ID,

        IR_DATA_RECIPIENT_MOTORS = IR_DATA_FIRST_RECIPIENT_ID,
        IR_DATA_RECIPIENT_LEDS,

    IR_DATA_LAST_RECIPIENT_ID = IR_DATA_RECIPIENT_LEDS
};

/// prototypes
uint32_t invue_is_ir_key_tx_idle(void);
uint32_t invue_is_ir_key_rx_idle(void);
void invue_ir_key_handler_app(void);
void processKeyInteraction( uint32_t ms_since_called );
void ir_send_packet( void );
void IR_TX_Complete( void );
void IR_DataByte_Received(uint8_t byte);
void init_irAppHandler( void );
void set_IR_status( uint32_t isDrivingLock, uint32_t lockingError, uint32_t isBusyForOtherReason  );
bool is_ir_comms_idle( void );
uint8_t ir_app_is_valid_ir_transaction_and_clear_if_so(enum ir_key_data_recipient_id);

// Triggers important "on init" changes immediately without needing to reboot.
void ir_call_if_enrollment_status_changes_in_nvmem(void);

#endif /* INVUE_IR_KEY_AU_H_ */
