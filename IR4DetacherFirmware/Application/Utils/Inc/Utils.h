/****************************************************************************
 FileName:     Utils.h
 Dependencies:
 Processor:
 Hardware:
 Complier:
 Company:      InVue


 Author				Date			Comment
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Nick McKendree		3/2021

*****************************************************************************
General description:


Dependencies:


usage:

****************************************************************************
Public Functions:

****************************************************************************/
#ifndef __APP_UTILS_H
#define __APP_UTILS_H

/****************************************************************************
						INCLUDES
*****************************************************************************/
#include <stddef.h>
#include <stdint.h>

/****************************************************************************
						GLOBAL TYPEDEFS
*****************************************************************************/

/****************************************************************************
                        DEFINES AND ENUMARATED VALUES
*****************************************************************************/

/****************************************************************************
                        MACROS
*****************************************************************************/
#define mTIME_TO_MS( hr, min, sec )			  ( 1000 * ( sec + ( min * 60 ) + ( hr * 60 * 60 )))
#ifndef MAX
#define MAX(a,b) ((a) > (b) ? a : b)
#endif

/****************************************************************************
                        GLOBAL FUNCTION PROTOTYPES
*****************************************************************************/
void runtime_IncrementTick( uint32_t mS );
uint32_t runtime_getTick( void );
uint32_t runTime_timeSince(uint32_t timeOrig);
void read_SystemVDD( void );
uint32_t get_SystemVDD( void );
uint16_t subsat_u16(uint16_t a, uint16_t b);									/* subtract b from a, saturating at 0 */
uint32_t subsat_u32(uint32_t a, uint32_t b);									/* subtract b from a, saturating at 0 */
uint32_t addsat_u32(uint32_t a, uint32_t b);									/* add b to a, saturating at UINT32_MAX */
uint16_t addsat_u16(uint16_t a, uint16_t b);
size_t min_size(size_t a, size_t b);											/* returns a or b, whichever is smallest */
void get_SystemVDD_stats( uint16_t *vdd_min, uint16_t *vdd_max, uint8_t *ignoredReadingCnt, uint16_t *ignoredReading );

/****************************************************************************
                        GLOBAL VARIABLES
******************************************************************************/

#endif /* __APP_UTILS_H */
