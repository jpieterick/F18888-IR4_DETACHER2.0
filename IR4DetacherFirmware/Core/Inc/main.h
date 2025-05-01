/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "periphdefs.h"

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define USER_BUTTON_Pin GPIO_PIN_13
#define USER_BUTTON_GPIO_Port GPIOC
#define VBOOST_FDBK_Pin GPIO_PIN_0
#define VBOOST_FDBK_GPIO_Port GPIOA
#define VBOOST_CAL_PWM_Pin GPIO_PIN_1
#define VBOOST_CAL_PWM_GPIO_Port GPIOA
#define VBOOST_ENABLE_Pin GPIO_PIN_2
#define VBOOST_ENABLE_GPIO_Port GPIOA
#define LED_RED_Pin GPIO_PIN_3
#define LED_RED_GPIO_Port GPIOA
#define LED_YELLOW_Pin GPIO_PIN_4
#define LED_YELLOW_GPIO_Port GPIOA
#define LED_GREEN_Pin GPIO_PIN_5
#define LED_GREEN_GPIO_Port GPIOA
#define WPT_PWM_Pin GPIO_PIN_6
#define WPT_PWM_GPIO_Port GPIOA
#define VIN_MONITOR_Pin GPIO_PIN_7
#define VIN_MONITOR_GPIO_Port GPIOA
#define DEBUG_RX_Pin GPIO_PIN_0
#define DEBUG_RX_GPIO_Port GPIOB
#define NFC_VOUT_SENSE_Pin GPIO_PIN_2
#define NFC_VOUT_SENSE_GPIO_Port GPIOB
#define DEBUG_TX_Pin GPIO_PIN_10
#define DEBUG_TX_GPIO_Port GPIOB
#define PIEZO_PWM_Pin GPIO_PIN_8
#define PIEZO_PWM_GPIO_Port GPIOA
#define IR_UART_TX_Pin GPIO_PIN_9
#define IR_UART_TX_GPIO_Port GPIOA
#define IR_UART_RX_Pin GPIO_PIN_10
#define IR_UART_RX_GPIO_Port GPIOA
#define CHARGE_EN_Pin GPIO_PIN_11
#define CHARGE_EN_GPIO_Port GPIOA
#define BATTERY_ENABLE_Pin GPIO_PIN_15
#define BATTERY_ENABLE_GPIO_Port GPIOA
#define NFC_POWER_ENABLE_Pin GPIO_PIN_6
#define NFC_POWER_ENABLE_GPIO_Port GPIOB
#define NFC_FD_INT_Pin GPIO_PIN_7
#define NFC_FD_INT_GPIO_Port GPIOB
#define NFC_I2C_SCL_Pin GPIO_PIN_8
#define NFC_I2C_SCL_GPIO_Port GPIOB
#define NFC_I2C_SDA_Pin GPIO_PIN_9
#define NFC_I2C_SDA_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
