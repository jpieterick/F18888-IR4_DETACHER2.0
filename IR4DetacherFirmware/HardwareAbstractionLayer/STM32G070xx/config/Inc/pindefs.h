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

// Pin Definition Enum.  MUST maintain same order as pin_defs[].
typedef enum pin_id
{
	BASE_BUTTON,
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
	NUM_PINS
}pin_id_t;

typedef enum
{
    IO_INTERRUPT_DISABLED,
    IO_INTERRUPT_RISING_EDGE,
    IO_INTERRUPT_FALLING_EDGE,
    IO_INTERRUPT_RISING_AND_FALLING_EDGES
}gpio_interrupt_config;

#if defined(USING_STM32CUBEIDE)

typedef struct
{
  uint32_t Pin;        /*!< Specifies the GPIO pins to be configured.
                           This parameter can be any value of @ref GPIO_pins */

} pin_config_t;

#else
typedef GPIO_InitTypeDef pin_config_t;
#endif

typedef GPIO_TypeDef pin_port_t;

extern pin_config_t const pin_defs[NUM_PINS];
extern pin_port_t* const port_defs[NUM_PINS];

#endif
