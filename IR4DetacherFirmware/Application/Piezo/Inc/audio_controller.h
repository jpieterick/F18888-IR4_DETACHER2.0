/**********************************
 * File: audio_controller.h
 * InVue
 * Copyright 2020
 **********************************/

#ifndef AUDIO_CONTROLLER_H_
#define AUDIO_CONTROLLER_H_

typedef enum { LOW_VOL_1, LOW_VOL_2, LOW_VOL_3, NORM_VOL }e_chirp_volume_levels;
typedef enum{ NOTIFY_IDLE, NOTIFY_UNLOCKED, NOTIFY_LOCKED }_NotificationType_e;

bool ac_buzzer_inactive(void);
//void ac_chirp_tone_ctrl(uint8_t num_chirps, bool low_tone);
void ac_chirp(uint8_t num_chirps);
void ac_activate_alarm_tone(bool manual_command);
void ac_deactivate_alarm_tone(bool manual_command);
void ac_set_piezo_pwm(int16_t period, uint16_t on_time);
void ac_audio_controller(uint16_t time_since_last_called_msec);
void ac_error_tone( uint8_t num_repeat);
void ac_change_chirp_volume_lvl( e_chirp_volume_levels level );
void ac_notification_locked( uint8_t num_times );
void ac_notification_unlocked( uint8_t num_times );

#endif // AUDIO_CONTROLLER_H_
