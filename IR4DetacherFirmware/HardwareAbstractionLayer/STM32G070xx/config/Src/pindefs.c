/**********************************
 * File: pindefs.c
 * InVue Security Products
 * Copyright 2022
 **********************************/

#include "pindefs.h"
#include "main.h"

#include "stm32g070xx.h"
#include "stm32g0xx.h"


#if defined(USING_STM32CUBEIDE)
pin_config_t const pin_defs[NUM_PINS] =
{
	// 	Pin						Mode					Pull			Speed			   		Alternate
	{USER_BUTTON_Pin,			GPIO_MODE_INPUT,    	GPIO_NOPULL,    GPIO_SPEED_FREQ_LOW,  	0u},
	{LED_RED_Pin,				GPIO_MODE_OUTPUT_PP,    GPIO_NOPULL,    GPIO_SPEED_FREQ_LOW,  	0u},
	{LED_YELLOW_Pin,			GPIO_MODE_OUTPUT_PP,    GPIO_NOPULL,    GPIO_SPEED_FREQ_LOW,  	0u},
	{LED_GREEN_Pin,				GPIO_MODE_OUTPUT_PP,    GPIO_NOPULL,    GPIO_SPEED_FREQ_LOW,  	0u},
	{WPT_PWM_Pin,				GPIO_MODE_AF_PP,    	GPIO_NOPULL,    GPIO_SPEED_FREQ_LOW,  	0u},
	{NFC_VOUT_SENSE_Pin,		GPIO_MODE_ANALOG,    	GPIO_NOPULL,    GPIO_SPEED_FREQ_LOW,  	0u},
	{PIEZO_PWM_Pin,				GPIO_MODE_AF_PP,    	GPIO_NOPULL,    GPIO_SPEED_FREQ_LOW,  	0u},
	{IR_UART_TX_Pin,			GPIO_MODE_AF_PP,    	GPIO_NOPULL,    GPIO_SPEED_FREQ_LOW,  	0u},
	{IR_UART_RX_Pin,			GPIO_MODE_AF_PP,    	GPIO_NOPULL,    GPIO_SPEED_FREQ_LOW,  	0u},
	{NFC_POWER_ENABLE_Pin,		GPIO_MODE_OUTPUT_PP,    GPIO_NOPULL,    GPIO_SPEED_FREQ_LOW,  	0u},
	{NFC_FD_INT_Pin,			GPIO_MODE_INPUT,    	GPIO_NOPULL,    GPIO_SPEED_FREQ_LOW,  	0u},
	{NFC_I2C_SCL_Pin,			GPIO_MODE_AF_PP,    	GPIO_NOPULL,    GPIO_SPEED_FREQ_LOW,  	0u},
	{NFC_I2C_SDA_Pin,			GPIO_MODE_AF_OD,    	GPIO_NOPULL,    GPIO_SPEED_FREQ_LOW,  	0u},
	{VBOOST_CAL_PWM_Pin,		GPIO_MODE_AF_OD,    	GPIO_NOPULL,    GPIO_SPEED_FREQ_LOW,  	0u},
};

#else
pin_config_t const pin_defs[NUM_PINS] =
{
		// 	Pin			Mode					Pull			Speed			   Alternate
  {		GPIO_PIN_8,  GPIO_MODE_OUTPUT_PP,    GPIO_NOPULL,    GPIO_SPEED_FREQ_LOW,  	0u}, 	//Example button,
  //LED_RED,
  //LED_YELLOW,
  //LED_GREEN,
  //WPT_PWM,
  //NFC_VOUT_SENSE,
  //PIEZO_PWM,
  //IR_UART_TX,
  //IR_UART_RX,
  //NFC_POWER_ENABLE,
  //NFC_FD_INT,
  //NFC_I2C_SCL,
  //NFC_I2C_SDA,

};
#endif


pin_port_t* const port_defs[NUM_PINS] =
{
	USER_BUTTON_GPIO_Port,
	LED_RED_GPIO_Port,
	LED_YELLOW_GPIO_Port,
	LED_GREEN_GPIO_Port,
	WPT_PWM_GPIO_Port,
	NFC_VOUT_SENSE_GPIO_Port,
	PIEZO_PWM_GPIO_Port,
	IR_UART_TX_GPIO_Port,
	IR_UART_RX_GPIO_Port,
	NFC_POWER_ENABLE_GPIO_Port,
	NFC_FD_INT_GPIO_Port,
	NFC_I2C_SCL_GPIO_Port,
	NFC_I2C_SDA_GPIO_Port,
	VBOOST_CAL_PWM_GPIO_Port,
};



