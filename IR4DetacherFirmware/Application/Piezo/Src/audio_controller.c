/** @file audio_controller.c
 *  @brief
 *
 *  @details
 *  To Use:

 *  Assumptions made:
 *
 *
 *  @author Nick M
 *  @bug No known bugs.
 *
 *  InVue Security Products
 *  Copyright 2023
 */

/***************************************************************************
INCLUDES
****************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "hal_gpio.h"
#include "hal_timer.h"
#include "periphdefs.h"
#include "audio_controller.h"
#include "audio_notes.h"

/****************************************************************************
                            TYPEDEFS
****************************************************************************/

typedef struct{
	uint16_t pwm_period;
	uint16_t pwm_dc;
	uint16_t duration;
}_alarmToneSteps_t;

typedef struct{
	_NotificationType_e type;
	uint8_t count;
	_alarmToneSteps_t *tone;
}_notificationInst_t;

/****************************************************************************
                            DEFINES
****************************************************************************/
#define NUM_ALARM_TONES          		8
#define ALARM_TONE_TIME_MSEC 	 		15
#define CHIRP_TONE_TIME_MSEC 	 		75
#define CHIRP_QUIET_TIME_MSEC 	  		75
#define ALARM_TONE_DUTY_CYCLE_PCT 		50
#define ALARM_ON_OFF_TIME_MSEC 			700
#define ERROR_BUZZ_FREQ					200
#define ERROR_BUZZ_DURATION_MSEC		100
#define NOTIFICATION_TONE_DELAY_MS 		125
//#define NUM_NOTIFICATION_TONES			4
#define NOTIFICATION_VOL_LOW_1_PCT		5
#define NOTIFICATION_VOL_LOW_2_PCT		10
#define NOTIFICATION_VOL_LOW_3_PCT		25
#define NOTIFICATION_VOL_NORM_PCT		NOTIFICATION_VOL_LOW_2_PCT

#define NUM_MOTOR_TONES          		5
#define MOTOR_TONE_TIME_MSEC 	 		75

/* map the target frequencies (in Hz) to timer periods (in counts) */
/* Frequency of Pitches come from pitches.h, an arduino library, found onlin */
#define PERIOD_COUNTS_200HZ 		(PWM_TIMER_HZ_TO_PERIOD_COUNTS(200,  PIEZO_PWM_PRESCALER))
#define PERIOD_COUNTS_440HZ 		(PWM_TIMER_HZ_TO_PERIOD_COUNTS(440,  PIEZO_PWM_PRESCALER))
#define PERIOD_COUNTS_500HZ 		(PWM_TIMER_HZ_TO_PERIOD_COUNTS(500,  PIEZO_PWM_PRESCALER))
#define PERIOD_COUNTS_550HZ 		(PWM_TIMER_HZ_TO_PERIOD_COUNTS(550,  PIEZO_PWM_PRESCALER))
#define PERIOD_COUNTS_660HZ 		(PWM_TIMER_HZ_TO_PERIOD_COUNTS(660,  PIEZO_PWM_PRESCALER))
#define PERIOD_COUNTS_988HZ /*B5*/	(PWM_TIMER_HZ_TO_PERIOD_COUNTS(988,  PIEZO_PWM_PRESCALER))
#define PERIOD_COUNTS_1319HZ/*E6*/	(PWM_TIMER_HZ_TO_PERIOD_COUNTS(1319,  PIEZO_PWM_PRESCALER))

#define PERIOD_COUNTS_1440HZ 		(PWM_TIMER_HZ_TO_PERIOD_COUNTS(1440, PIEZO_PWM_PRESCALER))
#define PERIOD_COUNTS_1550HZ 		(PWM_TIMER_HZ_TO_PERIOD_COUNTS(1550, PIEZO_PWM_PRESCALER))
#define PERIOD_COUNTS_1660HZ 		(PWM_TIMER_HZ_TO_PERIOD_COUNTS(1660, PIEZO_PWM_PRESCALER))

#define PERIOD_COUNTS_1976HZ/*B6*/	(PWM_TIMER_HZ_TO_PERIOD_COUNTS(1976,  PIEZO_PWM_PRESCALER))
#define PERIOD_COUNTS_2093HZ/*C7*/	(PWM_TIMER_HZ_TO_PERIOD_COUNTS(2093,  PIEZO_PWM_PRESCALER))
#define PERIOD_COUNTS_2217HZ/*CS7*/	(PWM_TIMER_HZ_TO_PERIOD_COUNTS(2217,  PIEZO_PWM_PRESCALER))
#define PERIOD_COUNTS_2637HZ/*E7*/	(PWM_TIMER_HZ_TO_PERIOD_COUNTS(2637,  PIEZO_PWM_PRESCALER))

#define PERIOD_COUNTS_2900HZ 		(PWM_TIMER_HZ_TO_PERIOD_COUNTS(2900, PIEZO_PWM_PRESCALER))
#define PERIOD_COUNTS_3200HZ 		(PWM_TIMER_HZ_TO_PERIOD_COUNTS(3200, PIEZO_PWM_PRESCALER))
#define PERIOD_COUNTS_3257HZ 		(PWM_TIMER_HZ_TO_PERIOD_COUNTS(3257, PIEZO_PWM_PRESCALER))
#define PERIOD_COUNTS_3314HZ 		(PWM_TIMER_HZ_TO_PERIOD_COUNTS(3314, PIEZO_PWM_PRESCALER))
#define PERIOD_COUNTS_3371HZ 		(PWM_TIMER_HZ_TO_PERIOD_COUNTS(3371, PIEZO_PWM_PRESCALER))
#define PERIOD_COUNTS_3429HZ 		(PWM_TIMER_HZ_TO_PERIOD_COUNTS(3429, PIEZO_PWM_PRESCALER))
#define PERIOD_COUNTS_3486HZ 		(PWM_TIMER_HZ_TO_PERIOD_COUNTS(3486, PIEZO_PWM_PRESCALER))
#define PERIOD_COUNTS_3543HZ 		(PWM_TIMER_HZ_TO_PERIOD_COUNTS(3543, PIEZO_PWM_PRESCALER))
#define PERIOD_COUNTS_3600HZ 		(PWM_TIMER_HZ_TO_PERIOD_COUNTS(3600, PIEZO_PWM_PRESCALER))
#define PERIOD_COUNTS_4000HZ 		(PWM_TIMER_HZ_TO_PERIOD_COUNTS(4000, PIEZO_PWM_PRESCALER))

#define INVUE_CHIRP_TONE_PERIOD		PERIOD_COUNTS_2900HZ

#define mFREQ_TO_DUTY_CYC_COUNTS(freqCounts, DC_pct)		(PWM_TIMER_DUTYCYCLE_TO_COUNTS(freqCounts, DC_pct))

//#define SILENT_ALARM_MODE
#ifdef SILENT_ALARM_MODE
#warning "SILENT_ALARM_MODE is active"
#endif

/****************************************************************************
                            GLOBAL VARIABLES
****************************************************************************/
// Note - These were originally const but i added a CLI command to adjust volume for customer demo. If the CLI command is removed, these can go back to const.
static const _alarmToneSteps_t alarm_tone[ NUM_ALARM_TONES ] = {
		{.pwm_period = PERIOD_COUNTS_3200HZ, .pwm_dc = mFREQ_TO_DUTY_CYC_COUNTS(PERIOD_COUNTS_3200HZ, ALARM_TONE_DUTY_CYCLE_PCT) /*DUTY_CYC_COUNTS_3200HZ*/, .duration = ALARM_TONE_TIME_MSEC },
		{.pwm_period = PERIOD_COUNTS_3257HZ, .pwm_dc = mFREQ_TO_DUTY_CYC_COUNTS(PERIOD_COUNTS_3257HZ, ALARM_TONE_DUTY_CYCLE_PCT) /*DUTY_CYC_COUNTS_3257HZ*/, .duration = ALARM_TONE_TIME_MSEC },
		{.pwm_period = PERIOD_COUNTS_3314HZ, .pwm_dc = mFREQ_TO_DUTY_CYC_COUNTS(PERIOD_COUNTS_3314HZ, ALARM_TONE_DUTY_CYCLE_PCT) /*DUTY_CYC_COUNTS_3314HZ*/, .duration = ALARM_TONE_TIME_MSEC },
		{.pwm_period = PERIOD_COUNTS_3371HZ, .pwm_dc = mFREQ_TO_DUTY_CYC_COUNTS(PERIOD_COUNTS_3371HZ, ALARM_TONE_DUTY_CYCLE_PCT) /*DUTY_CYC_COUNTS_3371HZ*/, .duration = ALARM_TONE_TIME_MSEC },
		{.pwm_period = PERIOD_COUNTS_3429HZ, .pwm_dc = mFREQ_TO_DUTY_CYC_COUNTS(PERIOD_COUNTS_3429HZ, ALARM_TONE_DUTY_CYCLE_PCT) /*DUTY_CYC_COUNTS_3429HZ*/, .duration = ALARM_TONE_TIME_MSEC },
		{.pwm_period = PERIOD_COUNTS_3486HZ, .pwm_dc = mFREQ_TO_DUTY_CYC_COUNTS(PERIOD_COUNTS_3486HZ, ALARM_TONE_DUTY_CYCLE_PCT) /*DUTY_CYC_COUNTS_3486HZ*/, .duration = ALARM_TONE_TIME_MSEC },
		{.pwm_period = PERIOD_COUNTS_3543HZ, .pwm_dc = mFREQ_TO_DUTY_CYC_COUNTS(PERIOD_COUNTS_3543HZ, ALARM_TONE_DUTY_CYCLE_PCT) /*DUTY_CYC_COUNTS_3543HZ*/, .duration = ALARM_TONE_TIME_MSEC },
		{.pwm_period = PERIOD_COUNTS_3600HZ, .pwm_dc = mFREQ_TO_DUTY_CYC_COUNTS(PERIOD_COUNTS_3600HZ, ALARM_TONE_DUTY_CYCLE_PCT) /*DUTY_CYC_COUNTS_3600HZ*/, .duration = ALARM_TONE_TIME_MSEC }
};

static _alarmToneSteps_t unlocked_tone[ NUM_MOTOR_TONES ] = {
		{.pwm_period = (PWM_TIMER_HZ_TO_PERIOD_COUNTS(NOTE_DS7, PIEZO_PWM_PRESCALER)), .pwm_dc = mFREQ_TO_DUTY_CYC_COUNTS( (PWM_TIMER_HZ_TO_PERIOD_COUNTS(NOTE_DS7, PIEZO_PWM_PRESCALER)), NOTIFICATION_VOL_NORM_PCT), .duration = 85 },
		{.pwm_period = (PWM_TIMER_HZ_TO_PERIOD_COUNTS(NOTE_DS7, PIEZO_PWM_PRESCALER)), .pwm_dc = mFREQ_TO_DUTY_CYC_COUNTS( (PWM_TIMER_HZ_TO_PERIOD_COUNTS(NOTE_DS7, PIEZO_PWM_PRESCALER)), NOTIFICATION_VOL_NORM_PCT), .duration = 25 },
		{.pwm_period = (PWM_TIMER_HZ_TO_PERIOD_COUNTS(((NOTE_DS7 + NOTE_FS7)/2), PIEZO_PWM_PRESCALER)), .pwm_dc = mFREQ_TO_DUTY_CYC_COUNTS( (PWM_TIMER_HZ_TO_PERIOD_COUNTS(((NOTE_DS7 + NOTE_FS7)/2), PIEZO_PWM_PRESCALER)), NOTIFICATION_VOL_NORM_PCT), .duration = 135 },
		{.pwm_period = (PWM_TIMER_HZ_TO_PERIOD_COUNTS(NOTE_FS7, PIEZO_PWM_PRESCALER)), .pwm_dc = mFREQ_TO_DUTY_CYC_COUNTS( (PWM_TIMER_HZ_TO_PERIOD_COUNTS(NOTE_FS7, PIEZO_PWM_PRESCALER)), NOTIFICATION_VOL_NORM_PCT), .duration = 85 },
		{.pwm_period = 0, .pwm_dc = 0, .duration = 50 }
};

static _alarmToneSteps_t locked_tone[ NUM_MOTOR_TONES ] = {
		{.pwm_period = (PWM_TIMER_HZ_TO_PERIOD_COUNTS(NOTE_FS7, PIEZO_PWM_PRESCALER)), .pwm_dc = mFREQ_TO_DUTY_CYC_COUNTS( (PWM_TIMER_HZ_TO_PERIOD_COUNTS(NOTE_FS7, PIEZO_PWM_PRESCALER)), NOTIFICATION_VOL_NORM_PCT), .duration = 85 },
		{.pwm_period = (PWM_TIMER_HZ_TO_PERIOD_COUNTS(NOTE_FS7, PIEZO_PWM_PRESCALER)), .pwm_dc = mFREQ_TO_DUTY_CYC_COUNTS( (PWM_TIMER_HZ_TO_PERIOD_COUNTS(NOTE_FS7, PIEZO_PWM_PRESCALER)), NOTIFICATION_VOL_NORM_PCT), .duration = 25 },
		{.pwm_period = (PWM_TIMER_HZ_TO_PERIOD_COUNTS(((NOTE_DS7 + NOTE_FS7)/2), PIEZO_PWM_PRESCALER)), .pwm_dc = mFREQ_TO_DUTY_CYC_COUNTS( (PWM_TIMER_HZ_TO_PERIOD_COUNTS(((NOTE_DS7 + NOTE_FS7)/2), PIEZO_PWM_PRESCALER)), NOTIFICATION_VOL_NORM_PCT), .duration = 135 },
		{.pwm_period = (PWM_TIMER_HZ_TO_PERIOD_COUNTS(NOTE_DS7, PIEZO_PWM_PRESCALER)), .pwm_dc = mFREQ_TO_DUTY_CYC_COUNTS( (PWM_TIMER_HZ_TO_PERIOD_COUNTS(NOTE_DS7, PIEZO_PWM_PRESCALER)), NOTIFICATION_VOL_NORM_PCT), .duration = 85 },
		{.pwm_period = 0, .pwm_dc = 0, .duration = 50 }
};

static _alarmToneSteps_t chirp_tone =  	  {.pwm_period = INVUE_CHIRP_TONE_PERIOD, .pwm_dc = mFREQ_TO_DUTY_CYC_COUNTS(INVUE_CHIRP_TONE_PERIOD, NOTIFICATION_VOL_NORM_PCT), .duration = CHIRP_TONE_TIME_MSEC };
static _alarmToneSteps_t chirp_tone_low = {.pwm_period = PERIOD_COUNTS_500HZ, .pwm_dc = mFREQ_TO_DUTY_CYC_COUNTS(PERIOD_COUNTS_500HZ, NOTIFICATION_VOL_NORM_PCT), .duration = CHIRP_TONE_TIME_MSEC };
static _alarmToneSteps_t buzz_tone =  	  {.pwm_period = PERIOD_COUNTS_200HZ, .pwm_dc = mFREQ_TO_DUTY_CYC_COUNTS(PERIOD_COUNTS_200HZ, NOTIFICATION_VOL_NORM_PCT), .duration = CHIRP_TONE_TIME_MSEC };

//static uint8_t notification_counter = 0;
static uint8_t chirp_counter      = 0;
static uint8_t error_counter 	  = 0;
static bool    chirp_low          = false;
static bool alarm_active          = false;
static bool state_override_active = false;  // used to turn on the piezo regardless of the state of the system security
static bool pwm_override_active   = false;  // used to turn on the piezo at a specific frequency (disable the audio controller)
static bool pwm_output_enabled    = false;
static _notificationInst_t notifications = {.count = 0, .type = NOTIFY_IDLE, .tone = NULL };

/****************************************************************************
                            FUNCTION PROTOTYPES
****************************************************************************/
static uint16_t ac_adjust_alarm_audio_level(uint32_t duty_cyle_count);

/****************************************************************************
                            CODE
****************************************************************************/

//Adding this function as a way to change the default duty cycle on the fly for testing and customer demo. This setting is not preserved in Flash
void ac_change_chirp_volume_lvl( e_chirp_volume_levels level )
{
	uint16_t dutyCyclePCT = NOTIFICATION_VOL_NORM_PCT;
	switch(level)
	{
		case LOW_VOL_1:
			dutyCyclePCT = NOTIFICATION_VOL_LOW_1_PCT;
			break;
		case LOW_VOL_2:
			dutyCyclePCT = NOTIFICATION_VOL_LOW_2_PCT;
			break;
		case LOW_VOL_3:
			dutyCyclePCT = NOTIFICATION_VOL_LOW_3_PCT;
			break;
		case NORM_VOL:
			dutyCyclePCT = NOTIFICATION_VOL_NORM_PCT;
			break;
		default:
			dutyCyclePCT = NOTIFICATION_VOL_NORM_PCT;
			break;
	}
	chirp_tone.pwm_dc = mFREQ_TO_DUTY_CYC_COUNTS(chirp_tone.pwm_period, dutyCyclePCT );
	chirp_tone_low.pwm_dc = mFREQ_TO_DUTY_CYC_COUNTS(chirp_tone_low.pwm_period, dutyCyclePCT );
	buzz_tone.pwm_dc = mFREQ_TO_DUTY_CYC_COUNTS(buzz_tone.pwm_period, dutyCyclePCT );
	locked_tone[0].pwm_dc = mFREQ_TO_DUTY_CYC_COUNTS(locked_tone[0].pwm_period, dutyCyclePCT );
	locked_tone[1].pwm_dc = mFREQ_TO_DUTY_CYC_COUNTS(locked_tone[1].pwm_period, dutyCyclePCT );
	locked_tone[2].pwm_dc = mFREQ_TO_DUTY_CYC_COUNTS(locked_tone[2].pwm_period, dutyCyclePCT );

	unlocked_tone[0].pwm_dc = mFREQ_TO_DUTY_CYC_COUNTS(unlocked_tone[0].pwm_period, dutyCyclePCT );
	unlocked_tone[1].pwm_dc = mFREQ_TO_DUTY_CYC_COUNTS(unlocked_tone[1].pwm_period, dutyCyclePCT );
	unlocked_tone[2].pwm_dc = mFREQ_TO_DUTY_CYC_COUNTS(unlocked_tone[2].pwm_period, dutyCyclePCT );
}

bool ac_buzzer_inactive(void)
{
	return ( ( chirp_counter == 0 ) && ( alarm_active == false ) && ( pwm_output_enabled == false ) && (error_counter == 0 ) && ( notifications.count == 0) );
}

void ac_activate_alarm_tone(bool manual_command)
{
	/* this function will prevent a change in state by the automated controller if the piezo has been commanded ON manually (i.e. via CLI)  */
#ifndef SILENT_ALARM_MODE
	if (manual_command)
	{
		alarm_active          = true;
		state_override_active = true;
	}
	else
	{
		if (false == state_override_active)
		{
			alarm_active = true;
		}
	}
#endif
}
void ac_deactivate_alarm_tone(bool manual_command)
{
	/* this function will prevent a change in state by the automated controller if the piezo has been commanded ON manually (i.e. via CLI)  */

	if (manual_command)
	{
		alarm_active          = false;
		state_override_active = false;
	}
	else
	{
		if (false == state_override_active)
		{
			alarm_active = false;
		}
	}
}

void ac_set_piezo_pwm(int16_t period, uint16_t on_time)
{
	hal_timer_set_pwm_output_period(TIMER_PIEZO_PWM, period, on_time);

	/* if disabling the piezo */
	if ((0 == period) || (0 == on_time))
	{
		pwm_override_active = false;
		pwm_output_enabled = false;
	}
	else
	{
		pwm_override_active = true;
		pwm_output_enabled = true;
	}
}
//
//void ac_chirp_tone_ctrl(uint8_t num_chirps, bool low_tone)
//{
//	if (low_tone)
//	{
//		chirp_low     = true;
//		chirp_counter = num_chirps;
//	}
//	else
//	{
//		if (false == chirp_low)
//		{
//			chirp_counter += num_chirps;
//			chirp_counter &= 0x0F; // limit to 15 chirps
//		}
//	}
//}

void ac_chirp(uint8_t num_chirps)
{
	chirp_counter += num_chirps;
	chirp_counter &= 0x0F; // limit to 15 chirps
}

void ac_error_tone( uint8_t num_repeat)
{
	error_counter += num_repeat;
	error_counter &= 0x0F; // limit to 15 chirps
}

void ac_notification_locked( uint8_t num_times )
{
	if( notifications.type == NOTIFY_IDLE )
	{
		notifications.type = NOTIFY_LOCKED;
		notifications.count = ( notifications.count + num_times) & 0x0F ;		// limit to 15 chirps
		notifications.tone = locked_tone;
	}
}

void ac_notification_unlocked( uint8_t num_times )
{
	if( notifications.type == NOTIFY_IDLE )
	{
		notifications.type = NOTIFY_UNLOCKED;
		notifications.count = ( notifications.count + num_times) & 0x0F ;		// limit to 15 chirps
		notifications.tone = unlocked_tone;
	}
}

void ac_audio_controller(uint16_t time_since_last_called_msec)
{
	static bool     chirp_active = false;
	static uint8_t  current_step = 0;
	static uint16_t time_since_last_tone        = 0;
	static uint16_t time_since_last_chirp_start = 0;
	static uint16_t time_since_last_chirp_stop  = 0;
    /* handle the AUDIO output pin definition to ensure the pin is driven LOW when inactive */
	if (ac_buzzer_inactive())
	{
		/* ensure the pin is a digital output and set LOW */
		hal_gpio_set_output(timer_defs[TIMER_PIEZO_PWM].pin_id, false);
		hal_gpio_set_pin_mode(timer_defs[TIMER_PIEZO_PWM].pin_id, pin_defs[ timer_defs[TIMER_PIEZO_PWM].pin_id ].Mode );
	}
	else
	{
		/* ensure the pin is in PWM mode */
//		hal_gpio_set_pin_mode(IO_AUDIO, GPIO_AF2_LPTIM1);
	}

	/* if a manual PWM command has been initiated */
	if (pwm_override_active)
	{
		return;
	}

	/* update the local timers */
	time_since_last_tone        += time_since_last_called_msec;
	time_since_last_chirp_start += time_since_last_called_msec;
	time_since_last_chirp_stop  += time_since_last_called_msec;

	if (alarm_active)
	{
		/* reset the number of chirps during an active alarm state to prevent
		 * any pending chirps from sounding after the alarm ends */
		chirp_counter = 0;
		error_counter = 0;
		notifications.count = 0;
		if ((time_since_last_tone >= ALARM_TONE_TIME_MSEC))
		{
			/* update the step */
			current_step = (current_step < (NUM_ALARM_TONES - 1)) ? (current_step + 1) : 0;

			/* set the PWM timer */
			uint16_t on_time =  ac_adjust_alarm_audio_level(alarm_tone[current_step].pwm_dc);
			hal_timer_set_pwm_output_period(TIMER_PIEZO_PWM, alarm_tone[current_step].pwm_period, on_time);
			pwm_output_enabled = true;
			/* reset the state timer */
			time_since_last_tone = 0;
		}
	}
	else
	{
		/* if there are pending chirps */
		if (chirp_counter > 0)
		{
			if (!chirp_active)
			{
				/* if time to start a chirp */
				if (time_since_last_chirp_stop >= CHIRP_QUIET_TIME_MSEC)
				{
					if (chirp_low)
					{
						hal_timer_set_pwm_output_period(TIMER_PIEZO_PWM, chirp_tone_low.pwm_period, ac_adjust_alarm_audio_level(chirp_tone_low.pwm_dc));
					}
					else
					{
						hal_timer_set_pwm_output_period(TIMER_PIEZO_PWM, chirp_tone.pwm_period, ac_adjust_alarm_audio_level(chirp_tone.pwm_dc));
					}
					pwm_output_enabled = true;
					time_since_last_chirp_start = 0;
					chirp_active                = true;
				}
			}
			else
			{
				/* if time to end the chirp */
				if (time_since_last_chirp_start >= CHIRP_TONE_TIME_MSEC)
				{
					hal_timer_set_pwm_output_period(TIMER_PIEZO_PWM, 0, 0);
					pwm_output_enabled = false;
					time_since_last_chirp_stop = 0;
					chirp_active = false;
					--chirp_counter;
				}
			}
		}
		else if (error_counter > 0)
		{
			if (!chirp_active)
			{
				/* if time to start a chirp */
				if (time_since_last_chirp_stop >= CHIRP_QUIET_TIME_MSEC)
				{
					hal_timer_set_pwm_output_period(TIMER_PIEZO_PWM, buzz_tone.pwm_period, ac_adjust_alarm_audio_level(buzz_tone.pwm_dc));
					pwm_output_enabled = true;
					time_since_last_chirp_start = 0;
					chirp_active                = true;
				}
			}
			else
			{
				/* if time to end the chirp */
				if (time_since_last_chirp_start >= ERROR_BUZZ_DURATION_MSEC)
				{
					hal_timer_set_pwm_output_period(TIMER_PIEZO_PWM, 0, 0);
					pwm_output_enabled = false;
					time_since_last_chirp_stop = 0;
					chirp_active = false;
					--error_counter;
				}
			}
		}
		else if( notifications.count > 0 && notifications.type != NOTIFY_IDLE )
		{
			if( pwm_output_enabled == false )
			{
				current_step = 0;
				pwm_output_enabled = true;
				time_since_last_tone = 0;
				hal_timer_set_pwm_output_period(TIMER_PIEZO_PWM, notifications.tone[current_step].pwm_period, ac_adjust_alarm_audio_level(notifications.tone[current_step].pwm_dc));
			}
			else
			{
				if ((time_since_last_tone >= notifications.tone[current_step].duration))
				{
					if( ++current_step >= NUM_MOTOR_TONES )
					{
						current_step = 0;
						if( notifications.count > 1 )
						{
							notifications.count--;
						}
						else
						{
							notifications.count = 0;
							hal_timer_set_pwm_output_period(TIMER_PIEZO_PWM, 0, 0);
							pwm_output_enabled = false;
							notifications.tone = NULL;
							notifications.type = NOTIFY_IDLE;
						}
					}
					if( notifications.count )
					{
						/* set the PWM timer */
						hal_timer_set_pwm_output_period(TIMER_PIEZO_PWM, notifications.tone[current_step].pwm_period, ac_adjust_alarm_audio_level(notifications.tone[current_step].pwm_dc));
						pwm_output_enabled = true;
						/* reset the state timer */
						time_since_last_tone = 0;
					}

				}
			}
		}
		else
		{
			chirp_low = false;
			hal_timer_set_pwm_output_period(TIMER_PIEZO_PWM, 0, 0);
			pwm_output_enabled = false;
		}
	}
}

static uint16_t ac_adjust_alarm_audio_level(uint32_t duty_cycle_count)
{
	return duty_cycle_count;
}
