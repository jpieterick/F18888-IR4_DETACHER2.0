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
  // 	Pin only
	{BASE_BUTTON_Pin},
	{LED_RED_Pin},
	{LED_YELLOW_Pin},
	{LED_GREEN_Pin},
	{WPT_PWM_Pin},
	{NFC_VOUT_SENSE_Pin},
	{PIEZO_PWM_Pin},
	{IR_UART_TX_Pin},
	{IR_UART_RX_Pin},
	{NFC_POWER_ENABLE_Pin},
	{NFC_FD_INT_Pin},
	{NFC_I2C_SCL_Pin},
	{NFC_I2C_SDA_Pin},

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
	BASE_BUTTON_GPIO_Port,
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
};



