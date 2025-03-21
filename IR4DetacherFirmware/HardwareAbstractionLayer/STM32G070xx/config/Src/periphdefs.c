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



/************ TIMERS ************/
// MUST maintain same order as enum timer_id.
timer_config_t const timer_defs[NUMBER_OF_TIMERS] =
{
		    //  timer,  	      type, 	  channel,    prescale_powers_of_2	timer_irq_cb
			{   TIM1,       TIM_GEN_PURPOSE, TIMER_CH1,   0,                   (void*)0}, // TIMER_PIEZO_PWM
			{   TIM3,       TIM_GEN_PURPOSE, TIMER_CH1,   0,                   (void*)0}, // TIMER_BLOCKING_DELAY
			{   TIM14,      TIM_GEN_PURPOSE, TIMER_CH1,   0,                   (void*)0}  // TIMER_COMMUNICATE_SHUTDOWN
};

irq_config_t irq_priorities[NUM_PRIORITIZED_IRQS] =
{
		// irq_num			nvic_priority_t
		{USART1_IRQn,	 	NVIC_PRIORITY_MID_HIGH},       // IRDot / Daisy_Chain
		{USART2_IRQn, 		NVIC_PRIORITY_HIGH},   		   // USART_Power
		{USART3_4_IRQn, 	NVIC_PRIORITY_MID_LOW},        // LORA_Dongle
};


__attribute__((weak))void MX_TIM1_Init(void)
{

}
