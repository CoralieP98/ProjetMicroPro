/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "stm32l1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "max7219_Yncrea2.h"
#include <stdio.h>
#include "iks01a3_motion_sensors.h"
#include "iks01a3_motion_sensors_ex.h"
#include <math.h>
#include <stdlib.h>
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
float get_heading(void);
void show_angle(void);
uint8_t get_led_count(float heading);
void set_leds(uint8_t count);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define B1_EXTI_IRQn EXTI15_10_IRQn
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define SPI_SCK_Pin GPIO_PIN_5
#define SPI_SCK_GPIO_Port GPIOA
#define SPI_MISO_Pin GPIO_PIN_6
#define SPI_MISO_GPIO_Port GPIOA
#define SPI_MOSI_Pin GPIO_PIN_7
#define SPI_MOSI_GPIO_Port GPIOA
#define BP4_Pin GPIO_PIN_5
#define BP4_GPIO_Port GPIOC
#define BP4_EXTI_IRQn EXTI9_5_IRQn
#define L0_Pin GPIO_PIN_1
#define L0_GPIO_Port GPIOB
#define L1_Pin GPIO_PIN_2
#define L1_GPIO_Port GPIOB
#define L2_Pin GPIO_PIN_10
#define L2_GPIO_Port GPIOB
#define L3_Pin GPIO_PIN_11
#define L3_GPIO_Port GPIOB
#define L4_Pin GPIO_PIN_12
#define L4_GPIO_Port GPIOB
#define L5_Pin GPIO_PIN_13
#define L5_GPIO_Port GPIOB
#define L6_Pin GPIO_PIN_14
#define L6_GPIO_Port GPIOB
#define L7_Pin GPIO_PIN_15
#define L7_GPIO_Port GPIOB
#define BP3_Pin GPIO_PIN_6
#define BP3_GPIO_Port GPIOC
#define BP3_EXTI_IRQn EXTI9_5_IRQn
#define SPI_CS_Pin GPIO_PIN_8
#define SPI_CS_GPIO_Port GPIOA
#define BP1_Pin GPIO_PIN_11
#define BP1_GPIO_Port GPIOA
#define BP1_EXTI_IRQn EXTI15_10_IRQn
#define BP2_Pin GPIO_PIN_12
#define BP2_GPIO_Port GPIOA
#define BP2_EXTI_IRQn EXTI15_10_IRQn
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
