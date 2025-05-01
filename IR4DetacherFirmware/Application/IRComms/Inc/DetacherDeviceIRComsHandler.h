/***************************************************************************
* Copyright © 2025 InVue Security Products, Charlotte, NC
* All Rights Reserved.
*
*  File: DetacherDeviceIRComsHandler.h
*
*  Description: Includes file for the Detacher IR Device side IR Communications
*  handler
****************************************************************************/
#ifndef DETACHER_IR_KEY_HANDLER_H_
#define DETACHER_IR_KEY_HANDLER_H_

#include "main.h"
#include "flash_controller.h"

// IR_UART_INDX must be set to the index of the UART that the IR interface is connected to.
#define IR_UART_INDX UART1INDX
/**************************************************************************
*   IRCommsDetacherIsAuthorized(void)
*
*   Description:	This functioon returns the DetacherIsAuthorized flag.
*
*  parameters:		None.
*
*  return values:   true when the detacher is authorized to access package
*  					protection devices.
*
***************************************************************************/
bool IRCommsDetacherIsAuthorized(void);

/**************************************************************************
*   void IRKeyHandlerInit(uart_hal_t* uart_hal)
*
*   Description: Functional Description of Routine
*
*  parameters:
*
*  return values:
*
***************************************************************************/
void IRKeyHandlerInit(uart_hal_t* uart_hal);

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
bool IRDeviceTxIdle(void);

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
bool IRDeviceRxIdle(void);

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
void invue_ir_key_handler_app(void);

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
bool trigger_ir_loopback_test( void )__attribute__ ((optimize(1)));

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
void IR_TX_Complete( void );

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
void init_irAppHandler( void );

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
void set_IR_status( uint32_t isDrivingLock, uint32_t lockingError, uint32_t isBusyForOtherReason  );

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
uint32_t ir_key_triggered_boot( void );

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
void check_ir_boot_source( void );

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
bool IRDeviceIRCommsAreIdle( void );

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
bool ir_mode_changed_externally( uint8_t mode );								// For testing only (tied to special CLI build)

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
bool sdc_cleared_externally( void );											// For testing only (tied to special CLI build)


#endif
