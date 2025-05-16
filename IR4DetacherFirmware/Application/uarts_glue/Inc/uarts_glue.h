/*
 * uarts_glue.h
 *
 *  Created on: Feb 7, 2023
 *      Author: jpieterick
 */

#ifndef UARTS_GLUE_H_
#define UARTS_GLUE_H_

#define UARTS_GL_USE_DEFAULT_BAUDRATE_VALUE (0)
#define UARTS_GL_USE_DEFAULT_CLOCK_HZ__VALUE (0)

#include "periphdefs.h"
#include "AppUartDriver.h"

AppUartDriver_t *uart_gl_GetUARTDriverPtr(uint8_t uartIndx);
void uart_gl_init_this_uart(uart_indx_t uartIndx);
void uart_gl_init_all_uarts(void);

void uart_gl_change_baudrate_and_clockHz(uart_indx_t uartIndx,uint32_t targetBaudRate,uint32_t TargetClockHz);
bool uart_gl_Uart_is_inactive(uart_indx_t uartIndx);

#endif /* UARTS_GLUE_H_ */
