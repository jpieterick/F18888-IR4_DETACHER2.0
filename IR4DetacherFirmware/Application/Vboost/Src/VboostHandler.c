/*************************************************************************** 
* Copyright © 2025 InVue Security Products, Charlotte, NC  
* All Rights Reserved. 
* 
*  File: VboostHandler.c
* 
*  Description: Functional Description of File Contents 
** 
****************************************************************************/
#include "stm32g070xx.h"
#include "tim.h"
#include "VboostHandler.h"

static uint16_t VboostPwmDutyCyclePct = 50;

bool GetVBoostVboostPwmDutyCyclePctFromFlash(void)
{
	// TODO: Write GetVBoostVboostPwmDutyCyclePctFromFlash()
	return false;
}

uint16_t GetVboostPwmDutyCyclePct(void)
{
	return VboostPwmDutyCyclePct;
}

void VboostStartPWM(void)
{
	HAL_TIMEx_PWMN_Start(&htim15, TIM_CHANNEL_1);
}

void VboostStopPWM(void)
{
	HAL_TIMEx_PWMN_Stop(&htim15, TIM_CHANNEL_1);
}
