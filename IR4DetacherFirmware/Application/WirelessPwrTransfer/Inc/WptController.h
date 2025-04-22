/*************************************************************************** 
* Copyright © 2024 InVue Security Products, Charlotte, NC  
* All Rights Reserved. 
* 
*  File: WptController.h 
* 
*  Description: As the name implies, this is the header file for the Wireless
*  Power Transfer Controller firmware.
** 
****************************************************************************/ 
#ifndef WPTCONTROLLER_H_
#define WPTCONTROLLER_H_
/****************************************************************************
                        Includes
****************************************************************************/
#include "periphdefs.h"
#include "flash_controller.h"

/****************************************************************************
                        DEFINES, ENUMARATED VALUES, AND  MACROS
*****************************************************************************/

/****************************************************************************
                        GLOBAL TYPEDEFS
*****************************************************************************/

/****************************************************************************
                        GLOBAL FUNCTION PROTOTYPES
*****************************************************************************/
void WptControllerInit(void);

bool WptSetCalibrationValue(uint16_t NewCalibrationValue);

#endif /* WPTCONTROLLER_H_ */
