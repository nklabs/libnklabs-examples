/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "stm32l0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
void MX_TIM3_Init(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define USER_BUTTON_Pin GPIO_PIN_13
#define USER_BUTTON_GPIO_Port GPIOC
#define USER_BUTTON_EXTI_IRQn EXTI4_15_IRQn
#define ARD_A0_Pin GPIO_PIN_0
#define ARD_A0_GPIO_Port GPIOA
#define ARD_A1_Pin GPIO_PIN_1
#define ARD_A1_GPIO_Port GPIOA
#define CONSOLE_TX_Pin GPIO_PIN_2
#define CONSOLE_TX_GPIO_Port GPIOA
#define CONSOLE_RX_Pin GPIO_PIN_3
#define CONSOLE_RX_GPIO_Port GPIOA
#define ARD_A2_Pin GPIO_PIN_4
#define ARD_A2_GPIO_Port GPIOA
#define ARD_D13_Pin GPIO_PIN_5
#define ARD_D13_GPIO_Port GPIOA
#define ARD_D12_Pin GPIO_PIN_6
#define ARD_D12_GPIO_Port GPIOA
#define ARD_D11_Pin GPIO_PIN_7
#define ARD_D11_GPIO_Port GPIOA
#define ARD_D1_Pin GPIO_PIN_4
#define ARD_D1_GPIO_Port GPIOC
#define ARD_D0_Pin GPIO_PIN_5
#define ARD_D0_GPIO_Port GPIOC
#define ARD_D10_Pin GPIO_PIN_0
#define ARD_D10_GPIO_Port GPIOB
#define ARD_A3_Pin GPIO_PIN_1
#define ARD_A3_GPIO_Port GPIOB
#define ARD_A4_Pin GPIO_PIN_11
#define ARD_A4_GPIO_Port GPIOB
#define ARD_A5_Pin GPIO_PIN_12
#define ARD_A5_GPIO_Port GPIOB
#define ARD_D6_Pin GPIO_PIN_14
#define ARD_D6_GPIO_Port GPIOB
#define ARD_D9_Pin GPIO_PIN_7
#define ARD_D9_GPIO_Port GPIOC
#define ARD_D7_Pin GPIO_PIN_8
#define ARD_D7_GPIO_Port GPIOA
#define ARD_D8_Pin GPIO_PIN_9
#define ARD_D8_GPIO_Port GPIOA
#define ARD_D2_Pin GPIO_PIN_10
#define ARD_D2_GPIO_Port GPIOA
#define ARD_D3_Pin GPIO_PIN_3
#define ARD_D3_GPIO_Port GPIOB
#define ARD_D5_Pin GPIO_PIN_4
#define ARD_D5_GPIO_Port GPIOB
#define ARD_D4_Pin GPIO_PIN_5
#define ARD_D4_GPIO_Port GPIOB
#define MAIN_I2C_SCL_Pin GPIO_PIN_8
#define MAIN_I2C_SCL_GPIO_Port GPIOB
#define MAIN_I2C_SDA_Pin GPIO_PIN_9
#define MAIN_I2C_SDA_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

// Name the devices we use

#define MAIN_CONSOLE_UART hlpuart1
extern UART_HandleTypeDef hlpuart1;

#define ARD_SPI hspi1
extern SPI_HandleTypeDef hspi1;

#define ARD_I2C hi2c1
extern I2C_HandleTypeDef hi2c1;

#define MAIN_WDT hiwdg
extern IWDG_HandleTypeDef hiwdg;

// Demo app functions called by main.h

void user_main(void);

// Called by stm32f0xx_it.c

void nk_uart_irq_handler(void);

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
