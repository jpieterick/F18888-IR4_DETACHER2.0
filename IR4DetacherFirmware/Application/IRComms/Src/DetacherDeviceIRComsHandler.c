/***************************************************************************
* Copyright © 2025 InVue Security Products, Charlotte, NC
* All Rights Reserved.
*
*  File: DetacherDeviceIRComsHandler.c
*
*  Description: This file contains the code for the IR4 Detacher IR Device
*  Behavior. This code handles communication with an IR4 key for the purpose
*  of being authorized to open Package Protection devices.
****************************************************************************/

#include "DetacherDeviceIRComsHandler.h"

#include "invue_ir_comms.h"
#include "uart_driver.h"

/****************************************************************************
                            DEFINES
****************************************************************************/

/****************************************************************************
                        STATIC FUNCTION PROTOTYPES
****************************************************************************/
static void processKeyInteraction( uint32_t ms_since_called );
static void IRDeviceSendPacket( void );
static void IRDeviceIR2Info(IR2_LockResults_e *ir2_lockState, IR2_Status_e *ir2_status);
static void IRDeviceIR4Info(IR4_LockStatus_e *ir4_lockState, IR4_DeviceState *ir4_status);

/****************************************************************************
                            STATIC VARIABLES
****************************************************************************/
static bool SDC_IsSet = false;

static IR2_Status_e appIR2_Status = IR2_OK;

static _ir_comms_ctx_s ir_comm_ctx = {
		.callbacks =
		{
			.fill_in_IR3_blob = NULL,
			.get_IR3_Pod_Status = NULL,
			.get_IR3_FW_Version = NULL,
			.get_legacy_code_reader_data = NULL,
			.get_IR2_info = IRDeviceIR2Info,
			.get_IR4_info = IRDeviceIR4Info,
			.smartRetail_reject_tout_tst_key_function = NULL,
			.smartRetail_reject_nonmatch_key_function = NULL
		},
		.device_chirps = 0,
		.ir4_data = {0},
		.product_id_product_line = PRODUCT_LINE_SMT_LOCK,
		.product_id_product_num = PRODUCT_LINE_SMT_LOCK_LIVE_LOCK,
		.my_sn = {0},
		.waiting_for_TOKEN_CT_WIPE_timeout_msec = 0,
		.legacy_device_type = G4DS_NULL_DEVICE,
		.sdc = {0},
		._priv_comm_vars = {0},
		.R_n_D_Key_supported = false,
		.ct_wipe_supported = false,
		.allow_IR_upgrade = true
};

static bool DetacherIsAuthorized = false;

/****************************************************************************
                            GLOBAL VARIABLES
****************************************************************************/


/**************************************************************************
*   void some_function(void)
*
*   Description: Functional Description of Routine
*
*  parameters:
*
*  return values:
*
***************************************************************************/
void DeviceIRComsHandlerInit(void)
{
	uart_driver_init_this_uart(IR_UART_INDX);



}

/**************************************************************************
*   void some_function(void)
*
*   Description: Functional Description of Routine
*
*  parameters:
*
*  return values:
*
***************************************************************************/
void IRDeviceSetSDC()
{
	// TODO: Write function IRDeviceSetSDC()
#warning "Function IRDeviceSetSDC() is just a stub."

}

/**************************************************************************
*   void some_function(void)
*
*   Description: Functional Description of Routine
*
*  parameters:
*
*  return values:
*
***************************************************************************/
#if 0
static void IRDeviceSendPacket( void )
{
	uint8_t byte;

	if (0 == cyclic_fifo_queue_get_item(&tx_queue, &byte) )
	{
		IR_transmitByte( byte );
		if( cyclic_fifo_queue_slots_used( &tx_queue ) != 0 )
		{
			are_there_more_ir_bytes_to_send = 1;
		}
	}
}


static void IRDeviceIR2Info(IR2_LockResults_e *ir2_lockState, IR2_Status_e *ir2_status)
{
	// TODO: Decide what to do with function IRDeviceIR2Info()
#if 0
	if( ir2_status )
	{
		// Assume this is only called from the ir1_ir3 module on key transaction
		// we really should report busy on first status request following sdc transfer and then fallback to
		// appIR2_Status which is set by the app's motor code.
		// This is implemented below in invue_ir_key_handler_app where the rtl flag is returned from invue_handle_ir_key_message.

		// Note: If on key power AND a non-volatile write is pending, report busy until completed.
		if( ir_key_triggered_boot() && is_nvDataWritePending() )
		{
			*ir2_status = IR2_BUSY;
		}
		else
		{
			*ir2_status = appIR2_Status;
		}
	}
	if( ir2_lockState )
	{
		if( ir_key_triggered_boot() == false )				// On external power, always report LATCHING Lock
		{
			*ir2_lockState = IR2_LOCK_SELF_LATCH;
		}
		else												// Battery power will be either locked or unlocked
		{
			if( lockStatus == UNLOCKED || lockStatus == LOCKING || lockStatus == LOCKING_ERROR )
			{
				*ir2_lockState = IR2_LOCK_UNLOCKED;
			}
			else
			{
				*ir2_lockState = IR2_LOCK_LOCKED;
			}
		}
	}
#endif
}

/**************************************************************************
*   void some_function(void)
*
*   Description: Functional Description of Routine
*
*  parameters:
*
*  return values:
*
***************************************************************************/
static void IRDeviceIR4Info(IR4_LockStatus_e *ir4_lockState, IR4_DeviceState *ir4_status)
{
	// IR4_DeviceState follows the same definitions as IR2_Status_e
	if( ir4_status )
	{
		// Assume this is only called from the ir1_ir3 module on key transaction
		// we really should report busy on first status request following sdc transfer and then fallback to
		// appIR2_Status which is set by the app's motor code.
		// This is implemented below in invue_ir_key_handler_app where the rtl flag is returned from invue_handle_ir_key_message.

		// Note: If on key power AND a non-volatile write is pending, report busy until completed.
		if( ir_key_triggered_boot() && is_nvDataWritePending() )
		{
			*ir4_status = IR4_DeviceBusy;
		}
		else
		{
			*ir4_status = (IR4_DeviceState)appIR2_Status;
		}
	}
	// TODO: In function IRDeviceIR4Info(), look at how to decide when the Detacher is authorized.
#if 0
	if( ir4_lockState )
	{
		// From the application, report self-latch, locked, or unlocked. The IR comms module may modify the result if using dual auth.
		if( ir_key_triggered_boot() == false )				// On external power, always report LATCHING Lock
		{
			*ir4_lockState = IR4_LOCK_UNLOCK_SELF_LATCH;
		}
		else												// Battery power will be either locked or unlocked
		{
			if( lockStatus == UNLOCKED || lockStatus == LOCKING || lockStatus == LOCKING_ERROR )
			{
				*ir4_lockState = IR4_LOCK_UNLOCKED;
			}
			else
			{
				*ir4_lockState = IR4_LOCK_LOCKED;
			}
		}
	}
#endif
}

/**************************************************************************
*   bool IRDeviceTxIdle(void)
*
*   Description: Returns TRUE if the IR byte handler is waiting for byte 0
*                and the transmitter is enabled.
*
*   parameters:  None.
*
*   return values: true - The transmitter is enabled and there are no bytes in the
*                         transmit queue.
*
*                  false - Either the transmitter is inactive and/or there are
*                          still bytes to be transmitted.
*
***************************************************************************/
bool IRDeviceTxIdle(void)
{
	return  ((uart_driver_tx_bytes_remaining(IR_UART_INDX) == 0) &&     			// there are no bytes to transmit
			 (uart_driver_is_transmitter_enabled(IR_UART_INDX) == false));   		// AND the transmitter is not enabled
}

/**************************************************************************
*   bool IRDeviceRxIdle(void)
*
*   Description: Functional Description of Routine
*
*  parameters: Returns TRUE if the IR byte handler is waiting for byte 0 and
*                      the receiver is enabled.
*
*  return values:
*
***************************************************************************/
bool IRDeviceRxIdle(void)
{
	return ((irComms_is_msg_parsing_idle(&ir_comm_ctx)     == true)  && 		// we are not receiving a packet
			(uart_driver_rx_bytes_remaining(IR_UART_INDX)  == 0)  &&			// AND there are no received bytes are
																				// waiting to be processed in the buffer
			(uart_driver_is_receiver_enabled(IR_UART_INDX) == true));   		// AND the receiver is enabled
}

/**************************************************************************
*   bool IRDeviceIRCommsAreIdle(void)
*
*   Description: Functional Description of Routine
*
*  parameters:
*
*  return values:
*
***************************************************************************/
//****************************************************************
//  bool IRDeviceIRCommsAreIdle(void)
//
//  Description: Returns true when both the receiver and transmitter
//				 are idle
//
//****************************************************************
bool IRDeviceIRCommsAreIdle( void )
{
	return (IRDeviceRxIdle() && IRDeviceTxIdle());
}

bool IRCommsDetacherIsAuthorized(void)
{
	return DetacherIsAuthorized;
}
#endif
