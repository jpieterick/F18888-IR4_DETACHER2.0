/**********************************
 * File: pindefs.h
 * InVue Security Products
 * Copyright 2025
 **********************************/

#ifndef PIN_DEFS_H_
#define PIN_DEFS_H_

#include <stdint.h>
#include "stm32g0xx.h"
#include "stm32g0xx_hal_gpio.h"
#include "periphdefs.h"

#define BUTTON_PRESSED (0)
#define BUTTON_RELEASED (1)

#define RXD_MODE_FOR_SLEEP            LL_GPIO_MODE_INPUT
#define RXD_MODE_FOR_RUN              LL_GPIO_MODE_INPUT
#define RXEN_MODE_FOR_SLEEP           LL_GPIO_MODE_INPUT
#define RXEN_MODE_FOR_RUN             LL_GPIO_MODE_INPUT
#define TXD_MODE_FOR_IDLE_SLEEP       LL_GPIO_MODE_INPUT
#define TXD_MODE_ACTIVE               LL_GPIO_MODE_OUTPUT
#define PIEZO_MODE_ACTIVE             LL_GPIO_MODE_OUTPUT
#define PIEZO_MODE_IDLE               LL_GPIO_MODE_INPUT

/*
 * LL_GPIO_MODE_INPUT
  *         @arg @ref LL_GPIO_MODE_OUTPUT
  *         @arg @ref LL_GPIO_MODE_ALTERNATE
  *         @arg @ref LL_GPIO_MODE_ANALOG
 */
// Pin Definition Enum.  MUST maintain same order as pin_defs[].
typedef enum pin_id
{
	USER_BUTTON,
	LED_RED,
	LED_YELLOW,
	LED_GREEN,
	WPT_PWM,
	NFC_VOUT_SENSE,
	PIEZO_PWM,
	IR_UART_TX,
	IR_UART_RX,
	NFC_POWER_ENABLE,
	NFC_FD_INT,
	NFC_I2C_SCL,
	NFC_I2C_SDA,
	VBOOST_CAL_PWM,
	NUM_PINS
}pin_id_t;

typedef enum
{
    IO_INTERRUPT_DISABLED,
    IO_INTERRUPT_RISING_EDGE,
    IO_INTERRUPT_FALLING_EDGE,
    IO_INTERRUPT_RISING_AND_FALLING_EDGES
}gpio_interrupt_config;


typedef GPIO_InitTypeDef pin_config_t;

typedef GPIO_TypeDef pin_port_t;

extern pin_config_t const pin_defs[NUM_PINS];
extern pin_port_t* const port_defs[NUM_PINS];

#endif
