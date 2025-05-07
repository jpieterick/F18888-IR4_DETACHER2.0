/***************************************************************************
* Copyright © 2025 InVue Security Products, Charlotte, NC
* All Rights Reserved.
*
*  File: WptController.c
*
*  Description: Code to handle the control of the Wireless Power Transfer
*               (WPT) functionality.
**
****************************************************************************/
#include "WptController.h"
#include "hal_timer.h"

#define WPT_DEFAULT_DUTY_CYCLE (50)

static uint16_t WptPercentDutyCycleTimes100 = WPT_DEFAULT_DUTY_CYCLE * 100;


/*****************************************************************
*   void WptControllerInit(void)
*
*   Description: This function initializes the Wireless Power Transfer
*                Controller.
*
*    parameters: None.
*
* return values: None
*
* ****************************************************************/
void WptControllerInit(void)
{
	// Get the Wireless Power Transfer percent duty cycle from flash
	// TODO: setup WPT duty cycle storage and retrieval to/from flash.


}

bool WptSetCalibrationValue(uint16_t NewCalibrationValue)
{
	return false;
}

void WptControllerStartPwm(void)
{
	// Turn on the WPT VBoost
	// TODO: Write code to turn on the WPT VBOOST

	// 	Set the WPT PWM duty cycle and then start the PWM output.
	hal_timer_RunPwAtDutyCycle(TIMER_WPT_PWM, (WptPercentDutyCycleTimes100));

}

void WptStopPwm(void)
{
	// calling hal_timer_set_pwm_output_period with zeros for the period and on time shuts down the PWM output.
	hal_timer_set_pwm_output_period(TIMER_WPT_PWM, 0, 0);
}
