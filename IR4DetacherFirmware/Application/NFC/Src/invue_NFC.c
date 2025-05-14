/** @file invue_NFC
 *  @brief communications protocol for NFC projects using NXP NTAG
 *
 *  @details
 *  To Use:

 *  Assumptions mode:
 *
 *
 *  @author M Warren
 *  @bug No known bugs.
 *
 *  InVue Security Products
 *  Copyright 2024
 */

/***************************************************************************
INCLUDES
****************************************************************************/
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "hal_rng.h"
#include "app_version.h"
#if USE_RTT_FOR_DEBUGGING
#include "rtt_debug.h"
#endif // USE_RTT_FOR_DEBUGGING
#include "pindefs.h"
#include "periphdefs.h"
#include "i2c_driver.h"
#include "hal_gpio.h"
#include "hal_interrupts.h"
#include "invue_NFC.h"
#include "ntag_driver.h"
#include "ntag_bridge.h"
#include "ntagInterfaceDriver.h"
#include "flash_glue.h"
#include "ir_key_glue.h"
#include "mkey_glue.h"
#include "invue_ir_comms.h"
#if USE_RTT_FOR_DEBUGGING
#include "SEGGER_RTT.h"
#endif // USE_RTT_FOR_DEBUGGING
#include "led.h"
#include "security.h"
#include "battery_glue.h"
#include "app_version.h"
#include "crc_ROM.h"
#include "stubs.h"

/****************************************************************************
                            DEFINES
****************************************************************************/

#define DEBUG_NFC 0
// USE_NFC_FD define allow NFC field detect only to work.  TODO: Remove when app available.
#define USE_NFC_FD 0
#define COUNTS_TO_DEBOUNCE_VOUT			3
#define NFC_LOST_COMMS_TIMEOUT_MS		2000
#define SWAP16(x) (((x & 0xFF00) >> 8) | ((x & 0x00FF) << 8))
#define HASH_SIZE 32


#define PLAINTEXT                 0
#define DEFAULT_SUBCMD            0

//NFC Position Defines
#define ENCRYPTION_BYTE           0
#define COMMAND                   1
#define SUBCOMMAND                2
#define PACKET                    3

// Provision Position Defines
#define PROV_SERIAL_NUMBER        5
#define PROV_CRC                 13
#define AUTH_KEY_START            5
#define ENC_KEY_START            21
#define AUTH_ENC_CRC             37

#define KEY_SIZE_256             32
#define KEY_SIZE_128             16
// OTA Command Defines
#define HASH_START                5
#define PACKET_START             37
#define FILE_SIZE                 5

// OTA Data Position Defines
#define DATA_START                2
#define OTA_PACKET_SIZE          44

// Set Config Defines
#define PACKET_1_START            5
#define NEXT_PACKET               4


#ifndef size_assert
#define size_assert( what, howmuch ) \
  typedef char what##_size_wrong_[( !!(sizeof(what) == howmuch) )*2-1 ]
#endif

/****************************************************************************

                            FUNCTION PROTOTYPES
****************************************************************************/
static void transitionState( nfc_status_e newState );

/****************************************************************************
                            GLOBAL VARIABLES
****************************************************************************/
extern bool nfc_field_detect;

extern NTAG_device_hndl_t ntagDevice;

const char *stateStrings[] = {
  "NFC_IDLE",
  "NFC_DETECTED",
  "NFC_GET_INFO",
  "NFC_UNLOCK",
  "NFC_READ_ENROLLMENT",
  "NFC_FUOTA",
  "NFC_LAST"
};

typedef enum
{
  NFC_CMD_READ,
  NFC_CMD_LOCK,
  NFC_CMD_UNLOCK,
  NFC_CMD_SET_CONFIG,
  NFC_CMD_OTA_COMMAND,
  NFC_CMD_OTA_DATA,
  NFC_CMD_READ_ENROLLMENT = 7,
  NFC_CMD_GET_INFO,
  NFC_CMD_TEST_POWER_ON,
  NFC_CMD_TEST_POWER_OFF,
  NFC_CMD_TEST_LOCK_CYCLE,
  NFC_CMD_SET_ENCRYPTION_KEYS,
  NFC_CMD_FACTORY_RESET,
  NFC_CMD_PROVISION_DEVICE,
  NFC_CMD_LAST
} nfc_command_e;

typedef enum
{
  NFC_DEFAULT_SUBCOMMAND
} nfc_default_subcommand_e;

// Factory reset Subcommands
typedef enum
{
  FACTORY_RESET_BASIC,
  FACTORY_RESET_INCLUDE_NFC,
} factory_reset_subcommands_e;

// OTA Subcommands
typedef enum
{
  NFC_START_OTA,
  NFC_CANCEL_OTA,
  NFC_COMPLETE_OTA,
  NFC_OTA_RESET
} ota_subcommands_e;

// OTA Data
typedef enum
{
  NFC_OTA_DATA_START = 2
} ota_data_e;

/****************************************************************************
                            STATIC VARIABLES
****************************************************************************/
static uint16_t device_status = 0;
static uint16_t battery_status = 0;
static uint8_t obfuscation_key[8] = {0};
static uint8_t enc_key[16] = {0};
static uint8_t auth_key[16] = {0};
static uint16_t lost_nfc_timer = 0;
static uint16_t time_since_nfc_last_called_msec = 0;
static nfc_status_e  current_NFC_State = NFC_IDLE;
static void platform_delay(uint32_t millisec);
static int32_t platform_write(uint8_t devAddr, const uint8_t *bufp, uint16_t len);
static int32_t platform_read(uint8_t devAddr, uint8_t *bufp, uint16_t len);
volatile uint32_t interruptActive = false;
volatile uint32_t nfc_field_changed = false;
static bool NFC_unlock = false;
static bool reset_register_flag = false;

#if NFC_OTA_SUPPORTED
static uint8_t OTA_update_hash[32] = {0};
#endif // NFC_OTA_SUPPORTED

static bool  firmware_update_in_progress = false;
static uint16_t  packetCounter = 100;
enum _unstage_get_info_stuff_
{
	GET_INFO_RESPONSE_SIZE			   = 64,
	GET_INFO_NUM_CC_BYTES			     =  4,
	GET_INFO_NUM_FW_REV_BYTES		   =  8,
	GET_INFO_NUM_SN_BYTES			     =  8,
	GET_INFO_NUM_PADDING_BYTES		 = 20,
	GET_INFO_NUM_BLANK_SPACE_BYTES =  7,
	GET_INFO_NUM_MAC_BYTES			   =  8
};
typedef struct __attribute__ ((__packed__)) _get_info_response_
{
	uint8_t		EncryptionId;
	uint8_t		MessageCode;
	uint8_t   SubCommand;
	uint16_t	SequenceNumber;
	uint8_t		SessionCCC[GET_INFO_NUM_CC_BYTES];
	uint8_t		FirmwareVersion[GET_INFO_NUM_FW_REV_BYTES];
	uint8_t		SerialNumber[GET_INFO_NUM_SN_BYTES];
	uint16_t	BatteryStatus;
	uint16_t	DeviceStatus;
	uint8_t		Padding[GET_INFO_NUM_PADDING_BYTES];
	uint8_t		BlankSpace[GET_INFO_NUM_BLANK_SPACE_BYTES];
	uint8_t		MAC[GET_INFO_NUM_MAC_BYTES];
} GET_INFO_RESPONSE;
// size_assert( GET_INFO_RESPONSE, GET_INFO_RESPONSE_SIZE );

static GET_INFO_RESPONSE get_info;
static uint32_t current_CCC = 0;
/****************************************************************************
                            CODE
****************************************************************************/
void generic_debug(const char * pcFormat, ...)
{
#if defined RTT_SUPPORT
    va_list args;
    SEGGER_RTT_SetTerminal(1);
    va_start( args, pcFormat );
    SEGGER_RTT_vprintf(0, pcFormat, &args);
    va_end( args );
    SEGGER_RTT_SetTerminal(0);
#endif
}


void init_get_info(void) //TODO - replace with real get info command.
{
  current_CCC = generate_CCC();
  get_info.EncryptionId   =   PLAINTEXT;
  get_info.MessageCode    =   NFC_CMD_GET_INFO;
  get_info.SubCommand     =   DEFAULT_SUBCMD;
  get_info.SequenceNumber =   packetCounter++;   // Packet Counter

  get_info.SessionCCC[0] =   current_CCC >> 24;   //  CCC random number
  get_info.SessionCCC[1] =   current_CCC >> 16;   //  CCC random number
  get_info.SessionCCC[2] =   current_CCC >>  8;   //  CCC random number
  get_info.SessionCCC[3] =   current_CCC;         //  CCC random number
  memcpy(&get_info.FirmwareVersion, &invue_fw_version_legacy, FW_ID_LENGTH_BYTES);
  if(!fcul_read( FLASH_KEY_SERIAL_NUMBER, (uint8_t *)get_info.SerialNumber, DEVICE_SN_BYTES))
  {
      generic_debug("Failed flash read of Serial Number\r\n");
  }
  else
  {
    generic_debug("Flash read of SN from flash: %u\r\n", get_info.SerialNumber[0]);
  }
  get_info.BatteryStatus = __builtin_bswap16((uint16_t) get_battery_life());
  get_info.DeviceStatus = __builtin_bswap16(device_status);
}

void update_get_info(void) // This one does not keep regenerating the CCC, that should only be generated on field detection.
{
    get_info.EncryptionId   =   PLAINTEXT;
    get_info.MessageCode    =   NFC_CMD_GET_INFO;
    get_info.SubCommand     =   DEFAULT_SUBCMD;
    get_info.SequenceNumber =   packetCounter++;   // Packet Counter

    get_info.SessionCCC[0] =   current_CCC >> 24;   //  CCC random number
    get_info.SessionCCC[1] =   current_CCC >> 16;   //  CCC random number
    get_info.SessionCCC[2] =   current_CCC >>  8;   //  CCC random number
    get_info.SessionCCC[3] =   current_CCC;         //  CCC random number
    memcpy(&get_info.FirmwareVersion, &invue_fw_version_legacy, FW_ID_LENGTH_BYTES);
    if(!fcul_read( FLASH_KEY_SERIAL_NUMBER, (uint8_t *)get_info.SerialNumber, DEVICE_SN_BYTES))
    {
        generic_debug("Failed flash read of Serial Number\r\n");
    }
    else
    {
      generic_debug("Flash read of SN from flash: %u\r\n", get_info.SerialNumber[0]);
    }
    get_info.BatteryStatus = __builtin_bswap16(get_battery_life());
    get_info.DeviceStatus = __builtin_bswap16(device_status);
}
/*****************************************************************
*  FncName    set_Device_Status
*  Description: Updates the device status.
*  parameters:  uint16_t device status
*  return:    void
*****************************************************************/
void set_Device_Status(uint16_t status)
{
  device_status |= status;
}

/*****************************************************************
*  FncName    clear_Device_Status
*  Description: Updates the device status.
*  parameters:  uint16_t device status
*  return:      void
*****************************************************************/
void clear_Device_Status(uint16_t status)
{
  device_status &= !status;
}

/*****************************************************************
*  FncName    rf_field_active
*  Description: Detects if rf field has been sensed.
*  parameters:  void
*  return:    true if field is detected
*****************************************************************/
bool is_rf_field_active( void )
{
	return hal_gpio_get_input(VNFC_OUT);
}

bool did_rf_field_just_change( void )
{
	bool temp = (bool)nfc_field_changed;
	nfc_field_changed = false;
	return temp;
}

/*****************************************************************
*  FncName    nfc_unlock_detected
*  Description: Set upon detection of NFC field.
*  parameters:  void
*  return:    true if field is detected
*****************************************************************/
bool nfc_unlock_detected( void )
{
	return NFC_unlock;
}

/*****************************************************************
*  FncName     nfc_is_interrupt_active
*  Description:Public function to know if the NFC INT is active
*  parameters: void
*  return:     true if NFC_INT is active (low)
*****************************************************************/
bool nfc_is_interrupt_active( void )
{
//	bool temp = interruptActive;
	interruptActive = false;
//	return temp;
	return interruptActive;
}

/*****************************************************************
*  FncName    clear_NFC_unlock
*  Description: Clear NFC unlock after starting motors.
*  parameters:  void
*  return:    void
*****************************************************************/
void clear_NFC_unlock(void)
{
  NFC_unlock = false;
}

/** @brief vout_int_callback
 *  @details Callback for Vout Interrupt
 *  @param[in] intNum: Interrupt #
 *  @return void
 */
void vout_int_callback( uint32_t intNum )
{
	(void)intNum;
	if((hal_gpio_get_input(VNFC_OUT ) ==  0) && (firmware_update_in_progress == false))
	{
//	    fwdl_write_init();  // Erase any downloaded files.
	    firmware_update_in_progress = false;
#if USE_RTT_FOR_DEBUGGING && DEBUG_NFC
	    debug_rtt_printf("Vout detected False\r\n");
#endif // USE_RTT_FOR_DEBUGGING
	}
	else
  {
#if USE_RTT_FOR_DEBUGGING && DEBUG_NFC
    debug_rtt_printf("Vout detected True\r\n");
#endif // USE_RTT_FOR_DEBUGGING
    transitionState(NFC_IDLE);
  }
	nfc_field_changed = true;
#if USE_NFC_FD == 1
  NFC_unlock = true;
#endif
}


/** @brief nfc_int_callback
 *  @details Callback for NFC Interrupt
 *  @param[in] intNum: Interrupt #
 *  @return void
 */
void nfc_int_callback( uint32_t intNum )
{
	(void)intNum;
	if( hal_gpio_get_input( NFC_INT) == 0 )
	{
		interruptActive = 1;
#if USE_RTT_FOR_DEBUGGING && DEBUG_NFC
		debug_rtt_printf("nfc detected True\r\n");
#endif // USE_RTT_FOR_DEBUGGING
	}
	else
	{
		interruptActive = 0;
#if USE_RTT_FOR_DEBUGGING && DEBUG_NFC
		debug_rtt_printf("nfc detected False\r\n");
#endif // USE_RTT_FOR_DEBUGGING
	}
}


/*****************************************************************
*  FncName    application_get_state_for_NFC
*  Description: Returns the current NFC state
*  parameters:  void
*  return:    nfc_status_e
*****************************************************************/
nfc_status_e application_get_state_for_NFC(void)
{
  return current_NFC_State;
}

static void transitionState( nfc_status_e newState )
{
	if(newState != current_NFC_State)
	{
		// TODO - harden this up
#if USE_RTT_FOR_DEBUGGING && DEBUG_NFC
		debug_rtt_printf("%s -> %s\r\n", stateStrings[current_NFC_State], stateStrings[newState]);
#endif // USE_RTT_FOR_DEBUGGING
		current_NFC_State = newState;

		  switch(current_NFC_State)
		  {
		    case NFC_IDLE:
		    	reset_register_flag = true;
				interruptActive = 0;
				break;
		    case NFC_GET_INFO:
		    	break;
		    default:
		    	break;
		  }
	}
}

void nfc_comms_HandleTimers( uint32_t elapsed_ms )
{
	const bool is_vout_detected = hal_gpio_get_input(VNFC_OUT );

	if(is_vout_detected == false && current_NFC_State != NFC_IDLE)
	{
		lost_nfc_timer += elapsed_ms;
	}
	time_since_nfc_last_called_msec += elapsed_ms;
}

/*****************************************************************
*  FncName    nfc_comms_handler
*  Description: Handles comms with NFC device
*  parameters:  time_since_last_called_msec
*               current_NFC_State
*  return:    void
*****************************************************************/
void nfc_comms_handler(ntagInterfaceHndl_t* ntag)
{
	_ntagErrorCodes result __attribute__ ((unused)) = NTAG_RESULT_OK;
	NTAG_TRANSFER_DIR_T dir;
	bool result_tf __attribute__ ((unused)) = false;
	static bool isInitialized = false;
	static uint8_t sram_buf[NTAG_MEM_SRAM_SIZE];
	static uint8_t currentCommand = 255;
	static uint16_t packets = 0;
	int8_t  updateStatus;
	size_t bytesReceived;
	uint8_t status;
	uint16_t temp_var;   // Holds temporary values so don't need dozens of temp variables.
	uint16_t temp_var1;
	uint32_t config_setting = 0;
	uint32_t filesize = 0; // Holds number of bytes to run hash calculation over.
	const bool is_vout_detected = hal_gpio_get_input(VNFC_OUT );

//	if( is_vout_detected )
//	{
//		NFC_unlock = true;
//	}


	if(lost_nfc_timer > NFC_LOST_COMMS_TIMEOUT_MS )
	{
		transitionState(NFC_IDLE);
	}

	if(isInitialized)
	{
		ntagInterface(ntag,
		              time_since_nfc_last_called_msec,
		              hal_gpio_get_input( NFC_INT) && is_vout_detected /*interrupt is only valid if vout is present since we cannot i2c comm with chip without it*/,
		              is_vout_detected );
		time_since_nfc_last_called_msec = 0;
	}

	switch(current_NFC_State)
	{
		case NFC_IDLE:

			lost_nfc_timer = 0;
			isInitialized = false;
			if( is_vout_detected )
			{
			  if (isInitialized == false)
			  {
			    init_get_info();
			  }
				result_tf = ntagIntf_setup( ntag );
#if USE_RTT_FOR_DEBUGGING && DEBUG_NFC
				debug_rtt_printf("Tag setup result %d\r\n", result_tf);
#endif // USE_RTT_FOR_DEBUGGING
				result = NTAG_SetPthruOnOff(ntag->devHandle, 1);
#if USE_RTT_FOR_DEBUGGING && DEBUG_NFC
				debug_rtt_printf("Passthru setup result %d\r\n", result);
#endif // USE_RTT_FOR_DEBUGGING
				transitionState(NFC_GET_INFO);
				result_tf = ntagIntf_sendData(ntag,(uint8_t *) &get_info, 64);   // Move data to the ram to send to the App.
				battery_life_event(BATTERY_LIFE_EVENT_NFC_EXCHANGE);
#if USE_RTT_FOR_DEBUGGING && DEBUG_NFC
				debug_rtt_printf("sendData result %d\r\n", result_tf);
#endif // USE_RTT_FOR_DEBUGGING
				result = NTAG_SetTransferDir(ntag->devHandle, I2C_TO_RF);  // We want to have the get info command be the first thing read.
#if USE_RTT_FOR_DEBUGGING && DEBUG_NFC
				debug_rtt_printf("Set Transfer I2C -> RF result = %u\n", result);
#endif // USE_RTT_FOR_DEBUGGING

				isInitialized = true;
			}
			break;
		case NFC_GET_INFO:
		  if(ntagIntf_dataRdyToTransmit(ntag))    // If we are executing a read command.
      {
//		      result_tf = ntagIntf_sendData(ntag, get_info, 64);   // Move data to the ram to send to the App.
//		      debug_rtt_printf("sendData result %d\r\n", result_tf);
		      result = NTAG_SetTransferDir(ntag->devHandle, RF_TO_I2C);  // Data has been read, change to be ready to receive a command.
#if USE_RTT_FOR_DEBUGGING && DEBUG_NFC
		      debug_rtt_printf("SetTransferDir RF ->I2C result = %u\n", result);
#endif // USE_RTT_FOR_DEBUGGING
      }
			if( ntagIntf_dataRdyToReceive(ntag))  // Is the tag ready to receive data?
			{
				ntagIntf_getData(ntag, sram_buf, &bytesReceived );   // Grab the data
				battery_life_event(BATTERY_LIFE_EVENT_NFC_EXCHANGE);

		    switch(sram_buf[COMMAND])
		    {
		      case NFC_CMD_UNLOCK:
		        switch(sram_buf[SUBCOMMAND])
		        {
              case NFC_DEFAULT_SUBCOMMAND:
                  NFC_unlock = true;
                  break;
		        }
		        break;

		      case NFC_CMD_GET_INFO:
            switch(sram_buf[SUBCOMMAND])
            {
              case NFC_DEFAULT_SUBCOMMAND:
                  update_get_info();
                  //NTAG_SetPthruOnOff(ntag->devHandle, 1);
                  NTAG_SetTransferDir(ntag->devHandle, I2C_TO_RF);
                  ntagIntf_sendData(ntag,(uint8_t *) &get_info, 64);
  				battery_life_event(BATTERY_LIFE_EVENT_NFC_EXCHANGE);
              break;

              default:  // unknown subcommand
              break;
            }
            break;

          case NFC_CMD_SET_CONFIG:
            switch(sram_buf[SUBCOMMAND])
            {
              case NFC_DEFAULT_SUBCOMMAND:
                switch(sram_buf[PACKET_1_START])
                {
                  case  1:
                    config_setting = sram_buf[PACKET_1_START + 1] << 24;
                    config_setting |= sram_buf[PACKET_1_START + 2] << 16;
                    config_setting |= sram_buf[PACKET_1_START + 3] << 8;
                    config_setting |= sram_buf[PACKET_1_START + 4];
                    temp_var = (uint16_t)config_setting;
                    temp_var = temp_var & ENROLLMENT_STATUS;
                    if(temp_var)
                    {
                        if(fcul_write(FLASH_KEY_ENROLL_STATUS, (uint8_t *) &temp_var, STATUS_SIZE) != FLASH_WRITE_ERROR )
                         {
                             set_Device_Status(temp_var); //Success
                         }
                         else
                         {
                             set_Device_Status(FLASH_ERROR);  // We had a Flash error
                         }
                    }
                    break;

                  default:
                    break;
                }
            }
            break;

		      case NFC_CMD_FACTORY_RESET:
            switch(sram_buf[SUBCOMMAND])
            {
              case FACTORY_RESET_INCLUDE_NFC :

                if (NTAG_SetPthruOnOff(ntag->devHandle, false) == NTAG_RESULT_OK)
                {
                    const uint16_t STATIC_LOCK_BYTES_ADDR   = (0x02 * 0x04) + 0x02;
                    const uint16_t CC_ADDR                  = (0x03 * 0x04) + 0x00;
                    const uint16_t DYNAMIC_LOCK_BYTES_ADDR  = (0xE2 * 0x04) + 0x00;
                    const uint16_t AUTH0_ADDR               = (0xE3 * 0x04) + 0x03;
                    const uint16_t PWD_ADDR                 = (0xE5 * 0x04) + 0x00;
                    const uint16_t PACK_ADDR                = (0xE6 * 0x04) + 0x00;

                    static const uint8_t static_lock_default[2U] = {
                        0x00,
                        0x00,
                    };

                    static const uint8_t cc_default[4U] = {
                        0x00,   // CC_0 Magic Number
                        0x00,   // CC_1 Mapping
                        0x00,   // CC_2 Size
                        0x00    // CC_3 Access Conditions
                    };

                    static const uint8_t dynamic_lock_default[3U] = {
                        0x00,
                        0x00,
                        0x00,
                    };

                    static const uint8_t auth0_default[1U] = { 0xFFU };

                    static const uint8_t pwd_default[4U] = {
                        0xFF,
                        0xFF,
                        0xFF,
                        0xFF
                    };

                    static const uint8_t pack_default[2U] = {
                        0x00,
                        0x00,
                    };

                    // The default value of the static lock bytes is 0000h.
                    result = NTAG_WriteBytes(ntag->devHandle, STATIC_LOCK_BYTES_ADDR, &static_lock_default[0U], sizeof(static_lock_default));
#if USE_RTT_FOR_DEBUGGING && DEBUG_NFC
                    debug_rtt_printf("WriteBytes slb result %d\r\n", result);
#endif // USE_RTT_FOR_DEBUGGING

                    // The default value of the CC is initialized with 00000000h during the IC production.
                    result = NTAG_WriteBytes(ntag->devHandle, CC_ADDR, &cc_default[0U], sizeof(cc_default));
#if USE_RTT_FOR_DEBUGGING && DEBUG_NFC
                    debug_rtt_printf("WriteBytes cc result %d\r\n", result);
#endif // USE_RTT_FOR_DEBUGGING

                    // The default value of the dynamic lock bytes is 000000h. The value of Byte 3 is always 00h.
                    result = NTAG_WriteBytes(ntag->devHandle, DYNAMIC_LOCK_BYTES_ADDR, &dynamic_lock_default[0U], sizeof(dynamic_lock_default));
#if USE_RTT_FOR_DEBUGGING && DEBUG_NFC
                    debug_rtt_printf("WriteBytes dlb result %d\r\n", result);
#endif // USE_RTT_FOR_DEBUGGING

                    // In the initial state of NTAG I2C plus, password protection is disabled by an AUTH0 value of FFh.
                    result = NTAG_WriteBytes(ntag->devHandle, AUTH0_ADDR, &auth0_default[0U], sizeof(auth0_default));
#if USE_RTT_FOR_DEBUGGING && DEBUG_NFC
                    debug_rtt_printf("WriteBytes auth0 result %d\r\n", result);
#endif // USE_RTT_FOR_DEBUGGING

                    // PWD and PACK are freely writable in this state
                    result = NTAG_WriteBytes(ntag->devHandle, PWD_ADDR, &pwd_default[0U], sizeof(pwd_default));
#if USE_RTT_FOR_DEBUGGING && DEBUG_NFC
                    debug_rtt_printf("WriteBytes pwd result %d\r\n", result);
#endif // USE_RTT_FOR_DEBUGGING

                    result = NTAG_WriteBytes(ntag->devHandle, PACK_ADDR, &pack_default[0U], sizeof(pack_default));
#if USE_RTT_FOR_DEBUGGING && DEBUG_NFC
                    debug_rtt_printf("WriteBytes pack result %d\r\n", result);
#endif // USE_RTT_FOR_DEBUGGING

                    result = NTAG_SetPthruOnOff(ntag->devHandle, true);
                }

              // fallthrough

              case FACTORY_RESET_BASIC:
                factory_reset();
                led_show_factory_reset();
		          break;

              default:  // unknown subcommand
              break;
            }
            break;

          case NFC_CMD_PROVISION_DEVICE:
              switch(sram_buf[SUBCOMMAND])
              {
                case NFC_DEFAULT_SUBCOMMAND:
                  temp_var = CRC_CalcCCITT( 0, &sram_buf[PROV_SERIAL_NUMBER], DEVICE_SN_BYTES);
                  temp_var = SWAP16(temp_var);
                  if(memcmp( &temp_var, &sram_buf[PROV_CRC], 2) == 0)     // Compare CRC's
                  {
//                      if( memcmp( _sn, our_serial_ram_copy/*ram copy*/,DEVICE_SN_BYTES ) != 0)
//                      {
//                        // we already have a serial number do not update
//                        // TODO: Set flag to say failed
//                      }
//                      else
                      {
                          irKey_diff_serial_and_update(&sram_buf[PROV_SERIAL_NUMBER]);
                          if(!fcul_read( FLASH_KEY_SERIAL_NUMBER, (uint8_t *)get_info.SerialNumber, DEVICE_SN_BYTES))
                            {
                              generic_debug("Failed flash read of SN from provision\r\n");
                              flash_debug();
                            }
                          else
                            {
                              generic_debug("Flash read of SN from provision: %u\r\n", get_info.SerialNumber[0]);
                              flash_debug();
                            }
//                          ntagIntf_sendData(ntag,(uint8_t *) &get_info, 64);   // Update get info command.
                      }
                      NTAG_SetTransferDir(ntag->devHandle, RF_TO_I2C);
                  }
                  break;

                  case 1:
                    temp_var = CRC_CalcCCITT( 0, &sram_buf[AUTH_KEY_START], KEY_SIZE_256);
                    temp_var = SWAP16(temp_var);
                    temp_var1 = sram_buf[AUTH_ENC_CRC] << 8;
                    temp_var1 = temp_var1 + sram_buf[AUTH_ENC_CRC + 1];
                    if(memcmp( &temp_var, &sram_buf[AUTH_ENC_CRC], 2) == 0)     // Compare CRC's
                    {
                        memcpy(&auth_key[0], &sram_buf[AUTH_KEY_START], KEY_SIZE_128 );
                        memcpy(&enc_key[0], &sram_buf[ENC_KEY_START], KEY_SIZE_128 );
                        obfuscation((uint8_t *)enc_key);
                        if( fcul_write(FLASH_KEY_FACTORY_KEY, enc_key, sizeof(enc_key)) != FLASH_WRITE_ERROR )
                        {

                        }
                        obfuscation((uint8_t *)auth_key);
                        if( fcul_write(FLASH_KEY_FACTORY_MAC, auth_key, sizeof(auth_key)) != FLASH_WRITE_ERROR )
                        {

                        }
                        status = 1;
                        fcul_write(FLASH_ENCRYTPION_STATUS, (uint8_t *)&status, 1);

                    }

                  break;

                default:  // unknown subcommand
                  break;
              }

              break;
#if NFC_OTA_SUPPORTED
          case NFC_CMD_OTA_COMMAND:
              switch(sram_buf[SUBCOMMAND])
              {

                case NFC_START_OTA:
                  memcpy(&OTA_update_hash, &sram_buf[HASH_START], HASH_SIZE );
                  packets =  (sram_buf[PACKET_START] << 8) + sram_buf[PACKET_START + 1];
                  debug_rtt_printf("Packets = %i", packets);
                  fwdl_write_init();  // Initial flash update space
                  firmware_update_in_progress = true;
                  result = NTAG_SetTransferDir(ntag->devHandle, RF_TO_I2C);
                  debug_rtt_printf("SetTransferDir RF ->I2C result = %u\n", result);
                  break;

                case NFC_CANCEL_OTA:
                  // We have been told to cancel update, erase any downloaded data
                  fwdl_write_init();  // Initial flash update space
                  firmware_update_in_progress = false;
                  packets = 0;
                  break;

                case NFC_COMPLETE_OTA:
                    packets = 0;
                    firmware_update_in_progress = false;
                    filesize = (sram_buf[FILE_SIZE] << 24) + (sram_buf[FILE_SIZE + 1] << 16) + (sram_buf[FILE_SIZE + 2] << 8) + (sram_buf[FILE_SIZE + 3]);
                    updateStatus = fwdl_write_finalize(OTA_update_hash, filesize);
                    memset(&sram_buf, 0, NTAG_MEM_SRAM_SIZE);   //clear buffer before updating
                    sram_buf[1] = NFC_CMD_OTA_COMMAND;
                    sram_buf[2] = NFC_COMPLETE_OTA;
                    sram_buf[3] = packetCounter << 8;
                    sram_buf[4] = packetCounter++;
                    sram_buf[5] = updateStatus;
                    sram_buf[6] = 0x80;
                    result = NTAG_SetTransferDir(ntag->devHandle, I2C_TO_RF); // Switch to send status
                    result_tf = ntagIntf_sendData(ntag,(uint8_t *) &sram_buf, NTAG_MEM_SRAM_SIZE);
    				battery_life_event(BATTERY_LIFE_EVENT_NFC_EXCHANGE);
                    result = NTAG_SetTransferDir(ntag->devHandle, RF_TO_I2C);  // Switch to receive OTA Reset
                  break;

                case NFC_OTA_RESET:
                    hal_interrupts_reboot();
                  break;

                default:  // unknown subcommand
                  break;
              }
              break;

          case NFC_CMD_OTA_DATA:
              NTAG_SetPthruOnOff(ntag->devHandle, 1);  // Don't know if this is needed, but we are going to make sure it is in pass thru mode.
//              ntag_dumpSessionConfigRegs(ntag);
//              result = NTAG_SetTransferDir(ntag->devHandle, RF_TO_I2C);
//              if( ntagIntf_dataRdyToReceive(ntag))  // Is the tag ready to receive data?
//              {
                ntagIntf_getData(ntag, sram_buf, &bytesReceived );
				battery_life_event(BATTERY_LIFE_EVENT_NFC_EXCHANGE);
                if (bytesReceived == 64)
                {
                    fwdl_write_fw_staging(&sram_buf[NFC_OTA_DATA_START], OTA_PACKET_SIZE);
                    packets--;
                    result = NTAG_SetTransferDir(ntag->devHandle, RF_TO_I2C);
                    debug_rtt_printf("SetTransferDir RF ->I2C result = %u\n", result);
                }
                if(packets == 0)
                {
                    NTAG_SetTransferDir(ntag->devHandle, RF_TO_I2C);
                }
//              }
#endif // NFC_OTA_SUPPORTED
          break;
			}
			break;
		      default:  // unknown Command
			break;
			}   // NFC_GET_INFO
	}  //current_NFC_State

}
