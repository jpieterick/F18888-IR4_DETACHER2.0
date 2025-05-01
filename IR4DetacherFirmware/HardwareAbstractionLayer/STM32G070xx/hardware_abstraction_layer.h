/*************************************************************************** 
* Copyright © 2024 InVue Security Products, Charlotte, NC  
* All Rights Reserved. 
* 
*  File: hardware_abstraction_layer.h 
* 
*  Description: Functional Description of File Contents 
** 
****************************************************************************/ 
#ifndef CONFIG_HARDWARE_ABSTRACTION_LAYER_H_
#define CONFIG_HARDWARE_ABSTRACTION_LAYER_H_
/****************************************************************************
                        Includes
****************************************************************************/

/****************************************************************************
                        DEFINES, ENUMARATED VALUES, AND  MACROS
*****************************************************************************/

/****************************************************************************
                        GLOBAL TYPEDEFS
*****************************************************************************/

/****************************************************************************
                        GLOBAL FUNCTION PROTOTYPES
*****************************************************************************/
bool product_has_alarm_audio_btn( void );
bool alarm_btn_pressed( void );
void alarm_status_led_ctrl( bool should_be_on );
bool should_box_led_show_security( void );
uint8_t what_is_my_product_family( void );
uint8_t what_is_my_product_id( void );
#endif /* CONFIG_HARDWARE_ABSTRACTION_LAYER_H_ */
