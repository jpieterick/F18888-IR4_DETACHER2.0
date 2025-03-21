#include "stdint.h" // needed for uint32_t
#define VTOR_REG (*((volatile uint32_t*)0xE000ED08))

extern int main(void);

extern void _estack(void);
extern unsigned int _etext;
extern unsigned int _sdata;
extern unsigned int _edata;
extern unsigned int _sidata;
extern unsigned int _sbss;
extern unsigned int _ebss;

//-----------------------------------------------------------------------------

void (* const vectors[])(void); // forward declaration

extern void NMI_Handler(void) __attribute__((__interrupt__));
extern void NMI_Handler(void);

extern void HardFault_Handler(void) __attribute__((__interrupt__));
extern void HardFault_Handler(void);

extern void SVC_Handler(void) __attribute__((__interrupt__));
extern void SVC_Handler(void);

extern void PendSV_Handler(void) __attribute__((__interrupt__));
extern void PendSV_Handler(void);

extern void SysTick_Handler(void) __attribute__((__interrupt__));
extern void SysTick_Handler(void);

extern void WWDG_IRQHandler(void) __attribute__((__interrupt__));
extern void WWDG_IRQHandler(void);

extern void RTC_TAMP_IRQHandler(void) __attribute__((__interrupt__));
extern void RTC_TAMP_IRQHandler(void);

extern void FLASH_IRQHandler(void) __attribute__((__interrupt__));
extern void FLASH_IRQHandler(void);

extern void RCC_IRQHandler(void) __attribute__((__interrupt__));
extern void RCC_IRQHandler(void);

extern void EXTI0_1_IRQHandler(void) __attribute__((__interrupt__));
extern void EXTI0_1_IRQHandler(void);

extern void EXTI2_3_IRQHandler(void) __attribute__((__interrupt__));
extern void EXTI2_3_IRQHandler(void);

extern void EXTI4_15_IRQHandler(void) __attribute__((__interrupt__));
extern void EXTI4_15_IRQHandler(void);

extern void DMA1_Channel1_IRQHandler(void) __attribute__((__interrupt__));
extern void DMA1_Channel1_IRQHandler(void);

extern void DMA1_Channel2_3_IRQHandler(void) __attribute__((__interrupt__));
extern void DMA1_Channel2_3_IRQHandler(void);

extern void DMA1_Ch4_7_DMAMUX1_OVR_IRQHandler(void) __attribute__((__interrupt__));
extern void DMA1_Ch4_7_DMAMUX1_OVR_IRQHandler(void);

extern void ADC1_IRQHandler(void) __attribute__((__interrupt__));
extern void ADC1_IRQHandler(void);

extern void TIM1_BRK_UP_TRG_COM_IRQHandler(void) __attribute__((__interrupt__));
extern void TIM1_BRK_UP_TRG_COM_IRQHandler(void);

extern void TIM1_CC_IRQHandler(void) __attribute__((__interrupt__));
extern void TIM1_CC_IRQHandler(void);

extern void TIM3_IRQHandler(void) __attribute__((__interrupt__));
extern void TIM3_IRQHandler(void);

extern void TIM6_IRQHandler(void) __attribute__((__interrupt__));
extern void TIM6_IRQHandler(void);

extern void TIM7_IRQHandler(void) __attribute__((__interrupt__));
extern void TIM7_IRQHandler(void);

extern void TIM14_IRQHandler(void) __attribute__((__interrupt__));
extern void TIM14_IRQHandler(void);

extern void TIM15_IRQHandler(void) __attribute__((__interrupt__));
extern void TIM15_IRQHandler(void);

extern void TIM16_IRQHandler(void) __attribute__((__interrupt__));
extern void TIM16_IRQHandler(void);

extern void TIM17_IRQHandler(void) __attribute__((__interrupt__));
extern void TIM17_IRQHandler(void);

extern void I2C1_IRQHandler(void) __attribute__((__interrupt__));
extern void I2C1_IRQHandler(void);

extern void I2C2_IRQHandler(void) __attribute__((__interrupt__));
extern void I2C2_IRQHandler(void);

extern void SPI1_IRQHandler(void) __attribute__((__interrupt__));
extern void SPI1_IRQHandler(void);

extern void SPI2_IRQHandler(void) __attribute__((__interrupt__));
extern void SPI2_IRQHandler(void);

extern void USART1_IRQHandler(void) __attribute__((__interrupt__));
extern void USART1_IRQHandler(void);

extern void USART2_IRQHandler(void) __attribute__((__interrupt__));
extern void USART2_IRQHandler(void);

extern void USART3_4_IRQHandler(void) __attribute__((__interrupt__));
extern void USART3_4_IRQHandler(void);



extern void Reset_Handler(void) __attribute__((__interrupt__));
void Reset_Handler(void)
{
    unsigned int *src, *dst;

    // Copy .data segment from Flash to RAM
    src = &_sidata;
    dst = &_sdata;
    while (dst < &_edata)
        *dst++ = *src++;

    // Zero out the .bss segment
    dst = &_sbss;
    while (dst < &_ebss)
        *dst++ = 0;

    VTOR_REG = (uint32_t)vectors;

    //__libc_init_array();

    main();
}


__attribute__ ((used, section(".isr_vector")))
void (* const vectors[])(void) =
{
    &_estack,                          /* 0 - Initial Stack Pointer Value */
    Reset_Handler,                     /* 1 - Reset                   */
    NMI_Handler,
    HardFault_Handler,
    0,                                 /* reserved                     */
    0,                                 /* reserved                     */
    0,                                 /* reserved                     */
    0,                                 /* reserved                     */
    0,                                 /* reserved                     */
    0,                                 /* reserved                     */
    0,                                 /* reserved                     */
    SVC_Handler,
    0,
    0,
    PendSV_Handler,
    SysTick_Handler,
    WWDG_IRQHandler,                   /* Window WatchDog              */
    0,                                 /* reserved                     */
    RTC_TAMP_IRQHandler,               /* RTC through the EXTI line    */
    FLASH_IRQHandler,                  /* FLASH                        */
    RCC_IRQHandler,                    /* RCC                          */
    EXTI0_1_IRQHandler,                /* EXTI Line 0 and 1            */
    EXTI2_3_IRQHandler,                /* EXTI Line 2 and 3            */
    EXTI4_15_IRQHandler,               /* EXTI Line 4 to 15            */
    0,                                 /* reserved                     */
    DMA1_Channel1_IRQHandler,          /* DMA1 Channel 1               */
    DMA1_Channel2_3_IRQHandler,        /* DMA1 Channel 2 and Channel 3 */
    DMA1_Ch4_7_DMAMUX1_OVR_IRQHandler, /* DMA1 Channel 4 to Channel 7, DMAMUX1 overrun */
    ADC1_IRQHandler,                   /* ADC1                         */
    TIM1_BRK_UP_TRG_COM_IRQHandler,    /* TIM1 Break, Update, Trigger and Commutation */
    TIM1_CC_IRQHandler,                /* TIM1 Capture Compare         */
    0,                                 /* reserved                     */
    TIM3_IRQHandler,                   /* TIM3                         */
    TIM6_IRQHandler,                   /* TIM6                         */
    TIM7_IRQHandler,                   /* TIM7                         */
    TIM14_IRQHandler,                  /* TIM14                        */
    TIM15_IRQHandler,                  /* TIM15                        */
    TIM16_IRQHandler,                  /* TIM16                        */
    TIM17_IRQHandler,                  /* TIM17                        */
    I2C1_IRQHandler,                   /* I2C1                         */
    I2C2_IRQHandler,                   /* I2C2                         */
    SPI1_IRQHandler,                   /* SPI1                         */
    SPI2_IRQHandler,                   /* SPI2                         */
    USART1_IRQHandler,                 /* USART1                       */
    USART2_IRQHandler,                 /* USART2                       */
    USART3_4_IRQHandler                /* USART3, USART4               */
};
