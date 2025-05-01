/****************************************************************************
FileName:     	Utils.c
Dependencies:
Processor:
Hardware:
Complier:
Company:      	InVue



 Author				Date			Comment
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Nick McKendree		3/2021

*****************************************************************************
General description:


Known limitations


****************************************************************************
INCLUDES
****************************************************************************/
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include "hal_adc.h"
#include "Utils.h"

/****************************************************************************
                        GLOBAL TYPEDEFS
*****************************************************************************/

/****************************************************************************
                            DEFINES
****************************************************************************/
#define TIME_MAX		UINT32_MAX

/****************************************************************************
                            GLOBAL MACROS
****************************************************************************/

/****************************************************************************
                            GLOBAL VARIABLES
****************************************************************************/
static uint32_t runtimeTick = 0;
static uint16_t systemVDD = MCU_DEFAULT_VDD_MV;
static uint16_t systemVDD_max = 0;
static uint16_t systemVDD_min = UINT16_MAX;
static uint8_t systemVDDrejectedCnt = 0;
static uint16_t lastRejectedVDDReading = 0;

/****************************************************************************
                            FUNCTION PROTOTYPES
****************************************************************************/

/****************************************************************************
                            CODE
****************************************************************************/

/*********************************************************************
Function:
Input:          void
Output:         void
Dependencies:
Description:
*********************************************************************/
void runtime_IncrementTick( uint32_t mS )
{
	runtimeTick += mS;
}

/*********************************************************************
Function:
Input:          void
Output:         void
Dependencies:
Description:
*********************************************************************/
uint32_t runtime_getTick( void )
{
	return runtimeTick;
}

/*********************************************************************
Function:
Input:          void
Output:         void
Dependencies:
Description:
*********************************************************************/
uint32_t runTime_timeSince(uint32_t timeOrig)
{
	volatile uint32_t now = runtime_getTick();   //volatile in case optimizer tries funny things (which it did!)

	if( now >= timeOrig)
	{
		return (now - timeOrig);
	}
	//rollover has occurred
	return( now + (1 + (TIME_MAX - timeOrig)));
}

/** @brief read_SystemVDD
 *  @details Read and store VDD voltage
 *  @param[in] void
 *  @return void
 */
void read_SystemVDD( void )
{
	uint32_t temp = hal_adc_get_vdd();
	if( temp < 2500 || temp > 3400 )
	{
		systemVDDrejectedCnt = addsat_u16(systemVDDrejectedCnt, 1);
		lastRejectedVDDReading = temp;
	}
	else
	{
		systemVDD = temp;
		if( systemVDD > systemVDD_max )
		{
			systemVDD_max = systemVDD;
		}
		if( systemVDD < systemVDD_min )
		{
			systemVDD_min = systemVDD;
		}
	}
}

/** @brief get_SystemVDD_stats
 *  @details
 *  @param[in] void
 *  @return void
 */
void get_SystemVDD_stats( uint16_t *vdd_min, uint16_t *vdd_max, uint8_t *ignoredReadingCnt, uint16_t *ignoredReading )
{
	if(vdd_min)
	{
		*vdd_min = systemVDD_min;
	}
	if( vdd_max )
	{
		*vdd_max = systemVDD_max;
	}
	if( ignoredReadingCnt )
	{
		*ignoredReadingCnt = systemVDDrejectedCnt;
	}
	if( ignoredReading )
	{
		*ignoredReading = lastRejectedVDDReading;
	}
}


/** @brief get_SystemVDD
 *  @details Get the last reading of VDD without running an ADC conversion
 *  @param[in] void
 *  @return uint32_t VDD
 */
uint32_t get_SystemVDD( void )
{
	return systemVDD;
}

/** @brief subsat_u16
 *  @details 16-bit subtract and stop at 0
 *  @param[in] uint16_t a, uint16_t b
 *  @return uint16_t result
 */
uint16_t subsat_u16(uint16_t a, uint16_t b)
{
    return  a > b ? a - b : 0;
}

/** @brief subsat_u32
 *  @details 32-bit subtract and stop at 0
 *  @param[in] uint32_t_t a, uint32_t_t b
 *  @return uint32_t result
 */
uint32_t subsat_u32(uint32_t a, uint32_t b)
{
    return  a > b ? a - b : 0;
}

/** @brief addsat_u32
 *  @details 32-bit subtract and stop at 0
 *  @param[in] uint32_t_t a, uint32_t_t b
 *  @return uint32_t result
 */
uint32_t addsat_u32(uint32_t a, uint32_t b)
{
    if( a > b )
    {
    	if( (a - b > b ) )
    	{
    		return UINT32_MAX;
    	}
    }
    return a + b;
}

/** @brief addsat_u16
 *  @details 16-bit subtract and stop at 0
 *  @param[in] uint16_t_t_t a, uint16_t_t_t b
 *  @return uint16_t_t result
 */
uint16_t addsat_u16(uint16_t a, uint16_t b)
{
    if( a > b )
    {
    	if( (a - b > b ) )
    	{
    		return UINT16_MAX;
    	}
    }
    return a + b;
}

/** @brief min_size
 *  @details min size
 *  @param[in] size_t_t_t a, size_t_t_t b
 *  @return size_t_t result
 */
size_t min_size(size_t a, size_t b)
{
    return a <= b ? a : b;
}
