/**********************************
 * File: pindefs.c
 * InVue Security Products
 * Copyright 2022
 **********************************/
#include <stdbool.h>
#include "periphdefs.h"
// BSP
#include "stm32g0xx.h"
//#include "live_defaults.h"
#include "periphdefs.h"
#include "usart.h"



/************ TIMERS ************/

// MUST maintain same order as enum timer_id.
/*
 * TIMER_PIEZO_PWM,
    TIMER_WPT_PWM,
	TIMER_VBOOST_CAL_PWM,
    TIMER_BLOCKING_DELAY,
	TIMER_COMMUNICATE_SHUTDOWN,
 */
timer_config_t timer_defs[NUMBER_OF_TIMERS] =
{
		    //  timer,  	      type, 	  channel,    _16b_prescaler			timer_irq_cb
			{   TIM1,       TIM_GEN_PURPOSE, TIMER_CH1,   PIEZO_PWM_PRESCALER,		(void*)0,	PIEZO_PWM}, // TIMER_PIEZO_PWM
			{   TIM3,       TIM_GEN_PURPOSE, TIMER_CH1,   WPT_PWM_PRESCALER,      	(void*)0,	WPT_PWM}, // TIMER_WPT_PWM
			{   TIM15,      TIM_GEN_PURPOSE, TIMER_CH1,   VBOOST_PRESCALER,    		(void*)0,	VBOOST_CAL_PWM}, // TIMER_VBOOST_CAL_PWM,
			{   TIM6,       TIM_BASIC,       TIMER_CH0,   BLOCKING_DELAY_PRESCALER, (void*)0,	NOT_USING_HW_PIN}, // TIMER_BLOCKING_DELAY,
		  //{   TIM14,      TIM_GEN_PURPOSE, TIMER_CH1,   0,                   		(void*)0,	NOT_USING_HW_PIN}  // TIMER_COMMUNICATE_SHUTDOWN
};

const uint16_t TimerArrValue[NUMBER_OF_TIMERS] =
{
	PIEZO_PWM_ARR_VAL, // TIMER_PIEZO_PWM has a variable period (ARR). This is a default value for testing.
	WPT_PWM_ARR_VAL, // TIMER_WPT_PWM,
	VBOOST_ARR_VAL, // TIMER_VBOOST_CAL_PWM,
	0, // TIMER_BLOCKING_DELAY isn't a pwm timer
};


irq_config_t irq_priorities[NUM_PRIORITIZED_IRQS] =
{
		// irq_num			nvic_priority_t
		{USART1_IRQn,	 	NVIC_PRIORITY_MID_HIGH},       // IRDot / Daisy_Chain
		{USART2_IRQn, 		NVIC_PRIORITY_HIGH},   		   // USART_Power
		{USART3_4_IRQn, 	NVIC_PRIORITY_MID_LOW},        // LORA_Dongle
};

uart_config_t uart_defs[NUMBER_OF_UARTS] =
{
	{
#ifdef USING_UART1
		{
		    USART1, // IR_COMM_UART
			&MX_USART1_UART_Init,
		    UART_TYPE_USART,
			TWO_WIRE,
			6553,
		    FREQ_SYSCLK,
		    (void*)0
	    }
	},
#endif
#ifdef USING_UART2
	{
		{
		    USART2,
			&MX_USART2_UART_Init,
		    UART_TYPE_USART,
			TWO_WIRE,
		    115200,
		    FREQ_SYSCLK,
		    (void*)0
		}
	},
#endif
#ifdef USING_UART3
	{
		{
		    USART3,
			&MX_USART3_UART_Init,
		    UART_TYPE_USART,
			TWO_WIRE,
		    115200,
		    FREQ_SYSCLK,
		    (void*)0
		}
	},
#endif
#ifdef USING_UART4
	{
		{
		    USART4,
			&MX_USART4_UART_Init,
		    UART_TYPE_USART,
			TWO_WIRE,
		    115200,
		    FREQ_SYSCLK,
		    (void*)0
		}
	},
#endif
};
