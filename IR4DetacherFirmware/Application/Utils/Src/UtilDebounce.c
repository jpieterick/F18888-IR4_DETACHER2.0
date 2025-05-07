/*
 * UtilDebounce.c
 *
 *  Created on: Aug 14, 2023
 *      Author: jpieterick
 */

#include "pindefs.h"
#include "periphdefs.h"
#include <stdint.h>
#include "UtilDebounce.h"
#include "hal_gpio.h"
#if USE_RTT_FOR_DEBUGGING && DEBUG_DEBOUNCE // Note that both of these should be #defined to 1 in periphdefs.h.
#include "rtt_debug.h"
#endif


#define DEBOUNCE_DEPTH (16) // This value must always be a power of 2. Note that this value actually sets the
							// number of readings and therefore the debounce time.
#define DEBOUNCE_WRAP  (DEBOUNCE_DEPTH - 1) // binary 1111b in the case of depth == 16.

#define NUM_PORT_2_DEBOUNCE (2)

static pin_port_t* const Ports2Debounce[NUM_PORT_2_DEBOUNCE] =
{
		GPIOC,
		GPIOB,
};

static uint32_t PortReadings[NUM_PORT_2_DEBOUNCE][DEBOUNCE_DEPTH];

static uint32_t DebouncedReadings[NUM_PORT_2_DEBOUNCE][2];

static uint8_t ThisReading = 0;

void UtilDebounceReadAndDebounceInputs(void)
{
	  uint8_t thisPort;
	  	uint16_t i;

	// Now debounce the inputs by anding and oring the members of the readings array.
	for (thisPort = 0;NUM_PORT_2_DEBOUNCE > thisPort; thisPort++)
	{
	   // Add this reading to the port readings array.
	   PortReadings[thisPort][ThisReading] = hal_gpio_read_port(Ports2Debounce[thisPort]);

	   DebouncedReadings[thisPort][0] = 0;
	   DebouncedReadings[thisPort][1] = 0xFFFFFFFF;

	   for (i = 0;DEBOUNCE_DEPTH > i;i++)
	   {
		   // debounce this port for input state == zero. If all members of the Port Readings array have a 0 in
		   // a specific bit position, that bit will be 0 in DebouncedLow for that port.
		   DebouncedReadings[thisPort][0] |= PortReadings[thisPort][i];

		   // debounce this port for input pin state == one. If all members of the Port Readings array have a 1 in
		   // a specific bit position, that bit will be 1 in DebouncedHigh for that port.
		   DebouncedReadings[thisPort][1] &= PortReadings[thisPort][i];
	   }

	}

	// Increment and wrap the reading number
	++ThisReading;
	ThisReading &= DEBOUNCE_WRAP; // This will cause the value of ThisReading to ngo back to zero when the value is incremented passed
									// the value of DEBOUNCE_WRAP.
}

// This function will return true if the specified pins state matches the indicated state.
bool UtilDebounceCheckPinState(enum pin_id pinId,bool state2BeChecked)
{
	bool retVal = false;
	uint8_t thisPort;

	// Find this pins port in the Ports2Debounce array
	for (thisPort = 0;NUM_PORT_2_DEBOUNCE > thisPort; thisPort++)
	{
		if (Ports2Debounce[thisPort] == port_defs[pinId])
		{
			// We found the port. We need to stop now.
			break;
		}
	}

	if (NUM_PORT_2_DEBOUNCE <= thisPort)
	{
		// We did not find this pins port in the Ports2Debounce array
#if USE_RTT_FOR_DEBUGGING && DEBUG_DEBOUNCE // Note that both of these should be #defined to 1 in periphdefs.h.
		debug_rtt_printf("Pin id %i points to a port that is not in the Ports2Debounce array\r\n",pinId);
#endif
		while(1);
	}
	else
	{
		if (true == state2BeChecked)
		{
			// Check for a one on the specified pins bit.
			if((DebouncedReadings[thisPort][1] & pin_defs[pinId].Pin) == pin_defs[pinId].Pin)
			{
				// This pins bit was set to one in all members of the PortReading array so return true:
				retVal = true;
			}
		}
		else
		{
			// Check for a zero on the specified pins bit.
			if((DebouncedReadings[thisPort][0] & pin_defs[pinId].Pin) == 0)
			{
				// This pins bit was set to zero in all members of the PortReading array so return true:
				retVal = true;
			}
		}
	}

	return retVal;
}
