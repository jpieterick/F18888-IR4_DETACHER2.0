#include <stdint.h> /* Needed for uint8_t, uint16_t, etc. */
#include <stdbool.h>
#include "hal_gpio.h"
#include "pindefs.h"
#include "ir_comms_product_list.h"		/* Needed for product id's */


// This file has been modified for the IR4 Detacher.

///////////////////////////////////////////////////////////////////////////////
// SOME DEFINES //////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// WATCHDOG, INTERRUPT CONTROL, REBOOTING ////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// DIGITAL IO ////////////////////////////////////////////////////////////////
bool product_has_alarm_audio_btn( void )
{
	return false;
}

bool alarm_btn_pressed( void )
{
	return false; //F1841 doesn't have an alarm button
}

void alarm_status_led_ctrl( bool should_be_on )
{
	// Leave empty - F1841 doesn't have this LED
	(void)should_be_on;
}

bool should_box_led_show_security( void )
{
	return true;
}

uint8_t what_is_my_product_family( void )
{
	// TODO: Fillin the product line/category.
	return PRODUCT_LINE_KEY;
}

uint8_t what_is_my_product_id( void )
{
	// TODO: Fill in the product ID.
	return PRODUCT_LINE_KEY_IR4_DETACHER;
}

///////////////////////////////////////////////////////////////////////////////
// TIMER RESOURCES ///////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// INTERRUPT VECTOR STUBS TO AVOID COMPILER ERRORS ///////////////////////////
#if 0

    void NMI_Handler(void) __attribute__((__interrupt__));
    void NMI_Handler(void)
    {}

    void HardFault_Handler(void) __attribute__((__interrupt__));
    void HardFault_Handler(void)
    {}

    void SVC_Handler(void) __attribute__((__interrupt__));
    void SVC_Handler(void)
    {}

    void PendSV_Handler(void) __attribute__((__interrupt__));
    void PendSV_Handler(void)
    {}

    void WWDG_IRQHandler(void) __attribute__((__interrupt__));
    void WWDG_IRQHandler(void)
    {}

    void RTC_TAMP_IRQHandler(void) __attribute__((__interrupt__));
    void RTC_TAMP_IRQHandler(void)
    {}

    void FLASH_IRQHandler(void) __attribute__((__interrupt__));
    void FLASH_IRQHandler(void)
    {}

    void RCC_IRQHandler(void) __attribute__((__interrupt__));
    void RCC_IRQHandler(void)
    {}

    void EXTI0_1_IRQHandler(void) __attribute__((__interrupt__));
    void EXTI0_1_IRQHandler(void)
    {}

    void EXTI2_3_IRQHandler(void) __attribute__((__interrupt__));
    void EXTI2_3_IRQHandler(void)
    {}

    void EXTI4_15_IRQHandler(void) __attribute__((__interrupt__));
    void EXTI4_15_IRQHandler(void)
    {}

    void DMA1_Channel1_IRQHandler(void) __attribute__((__interrupt__));
    void DMA1_Channel1_IRQHandler(void)
    {}

    void DMA1_Channel2_3_IRQHandler(void) __attribute__((__interrupt__));
    void DMA1_Channel2_3_IRQHandler(void)
    {}

    void DMA1_Ch4_7_DMAMUX1_OVR_IRQHandler(void) __attribute__((__interrupt__));
    void DMA1_Ch4_7_DMAMUX1_OVR_IRQHandler(void)
    {}

    void ADC1_IRQHandler(void) __attribute__((__interrupt__));
    void ADC1_IRQHandler(void)
    {}

    void TIM1_BRK_UP_TRG_COM_IRQHandler(void) __attribute__((__interrupt__));
    void TIM1_BRK_UP_TRG_COM_IRQHandler(void)
    {}

    void TIM1_CC_IRQHandler(void) __attribute__((__interrupt__));
    void TIM1_CC_IRQHandler(void)
    {}

    void TIM3_IRQHandler(void) __attribute__((__interrupt__));
    void TIM3_IRQHandler(void)
    {}

    void TIM6_IRQHandler(void) __attribute__((__interrupt__));
    void TIM6_IRQHandler(void)
    {}

    void TIM7_IRQHandler(void) __attribute__((__interrupt__));
    void TIM7_IRQHandler(void)
    {}

    void TIM14_IRQHandler(void) __attribute__((__interrupt__));
    void TIM14_IRQHandler(void)
    {}

    void TIM15_IRQHandler(void) __attribute__((__interrupt__));
    void TIM15_IRQHandler(void)
    {}

    void TIM16_IRQHandler(void) __attribute__((__interrupt__));
    void TIM16_IRQHandler(void)
    {}

    void TIM17_IRQHandler(void) __attribute__((__interrupt__));
    void TIM17_IRQHandler(void)
    {}

    void I2C1_IRQHandler(void) __attribute__((__interrupt__));
    void I2C1_IRQHandler(void)
    {}

    void I2C2_IRQHandler(void) __attribute__((__interrupt__));
    void I2C2_IRQHandler(void)
    {}

    void SPI1_IRQHandler(void) __attribute__((__interrupt__));
    void SPI1_IRQHandler(void)
    {}

    void SPI2_IRQHandler(void) __attribute__((__interrupt__));
    void SPI2_IRQHandler(void)
    {}

#ifdef USART_IRQS_NOT_DEFINED
    void USART1_IRQHandler(void) __attribute__((__interrupt__));
    void USART1_IRQHandler(void)
    {}

    void USART2_IRQHandler(void) __attribute__((__interrupt__));
    void USART2_IRQHandler(void)
    {}

    void USART3_4_IRQHandler(void) __attribute__((__interrupt__));
    void USART3_4_IRQHandler(void)
    {}
#endif
#endif

