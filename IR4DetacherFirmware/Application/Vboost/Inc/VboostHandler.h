/*************************************************************************** 
* Copyright © 2024 InVue Security Products, Charlotte, NC  
* All Rights Reserved. 
* 
*  File: VboostHandler.h 
* 
*  Description: Functional Description of File Contents 
** 
****************************************************************************/ 
#ifndef VBOOSTHANDLER_H_
#define VBOOSTHANDLER_H_
/****************************************************************************
                        Includes
****************************************************************************/
#include <stdint.h>
#include <stdbool.h>

/****************************************************************************
                        DEFINES, ENUMARATED VALUES, AND  MACROS
*****************************************************************************/

/****************************************************************************
                        GLOBAL TYPEDEFS
*****************************************************************************/

/****************************************************************************
                        GLOBAL FUNCTION PROTOTYPES
*****************************************************************************/
// TODO: Add function header comments to VboostHandler.h.

uint16_t GetVboostPwmDutyCyclePct(void);
bool GetVBoostVboostPwmDutyCyclePctFromFlash(void);
void VboostStartPWM(void);
void VboostStopPWM(void);

#endif /* VBOOSTHANDLER_H_ */
