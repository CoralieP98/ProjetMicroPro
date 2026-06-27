/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "iks01a3_motion_sensors.h"
#include "iks01a3_motion_sensors_ex.h"
#include <math.h>
#include <stdlib.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
float get_heading(void);
void show_angle(void);
uint8_t get_led_count(float heading);
void set_leds(uint8_t count);
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
IKS01A3_MOTION_SENSOR_Axes_t accel_data;
IKS01A3_MOTION_SENSOR_Axes_t mag_value;
int32_t myThreshold = 1;
uint8_t id;
float x_min=-834,x_max=-259, y_min=-24, y_max=586,y=0,x=0;
float x_offset,y_offset;
char str[9];
int target_angle=0;
typedef enum {
    WAIT_START = 0,
    TARGET_GENERATED,
    GUESS_MODE,
    RESULT
} GameState;

GameState state = WAIT_START;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_SPI1_Init();
  MAX7219_DisplayTestStart();
  HAL_Delay(2000);
  MAX7219_DisplayTestStop();
  /* USER CODE BEGIN 2 */
  printf("Hello Project\r\n");

   if(IKS01A3_MOTION_SENSOR_Init(IKS01A3_LIS2MDL_0, MOTION_MAGNETO) == !BSP_ERROR_NONE ){
     printf("magneto initialization failed\r\n");
   }
   IKS01A3_MOTION_SENSOR_SetOutputDataRate(IKS01A3_LIS2MDL_0, MOTION_MAGNETO, 100.0f);
   IKS01A3_MOTION_SENSOR_SetFullScale(IKS01A3_LIS2MDL_0, MOTION_MAGNETO, 50);

   if(IKS01A3_MOTION_SENSOR_GetAxes(IKS01A3_LIS2MDL_0, MOTION_MAGNETO, &mag_value)== !BSP_ERROR_NONE){
     printf("Error get axes\r\n");
   }else{


     printf("x value:%ld\r\n",mag_value.x);
     printf("y value:%ld\r\n",mag_value.y);
     printf("z value:%ld\r\n",mag_value.z);
     x_offset=(x_max+x_min)/2;
     y_offset=(y_max+y_min)/2;

     printf("x value:%ld\r\n",accel_data.x);
     	  printf("y value:%ld\r\n",accel_data.y);
     	  printf("z value:%ld\r\n",accel_data.z);

   }
   srand(HAL_GetTick());
   MAX7219_DisplayChar(1,'A');
   MAX7219_DisplayChar(2,'A');
   MAX7219_DisplayChar(3,'A');
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	 /* if(IKS01A3_MOTION_SENSOR_GetAxes(IKS01A3_LIS2MDL_0, MOTION_MAGNETO, &mag_value)== !BSP_ERROR_NONE){
	      printf("Error get axes\r\n");
	    }else{
	    	if(mag_value.x<x_min){x_min=mag_value.x;}
	    	if(mag_value.x>x_max){x_max=mag_value.x;}
	    	if(mag_value.y<y_min){y_min=mag_value.y;}
	    	if(mag_value.y>y_max){y_max=mag_value.y;}
	    	printf("x value:%ld\r\n",mag_value.x);
	        printf("y value:%ld\r\n",mag_value.y);
	        printf("z value:%ld\r\n",mag_value.z);


	    	y=mag_value.y-y_offset;
	    	x=mag_value.x-x_offset;
	        float heading = atan2f((float)y,
	                               (float)x);

	        heading = heading * 180.0f / M_PI;

	        if(heading < 0)
	        {
	            heading += 360.0f;
	        }


	        target_angle=rand()%360;
	        printf("Cap aleatoire= %d deg\r\n", target_angle);
	        printf("Cap = %f deg\r\n", heading);
	        printf("x_min : %f\n\r",x_min);
	        printf("x_max : %f\n\r",x_max);
	        printf("y_min : %f\n\r",y_min);
	        printf("y_max : %f\n\r",y_max);
	        printf("***************\r\n");
	      //  MAX7219_DisplayChar(1, (int)heading);
	        snprintf(str, sizeof(str), "%03.0f", heading);

	        MAX7219_DisplayChar(1,str[0]);
	        MAX7219_DisplayChar(2,str[1]);
	        MAX7219_DisplayChar(3,str[2]);
	        MAX7219_DisplayChar(4,'o');

	    }

	  HAL_Delay(1000);   */



	  	    //void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

	  show_angle();
  }



    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLL_DIV3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, L0_Pin|L1_Pin|L2_Pin|L3_Pin
                          |L4_Pin|L5_Pin|L6_Pin|L7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : B1_Pin BP3_Pin */
  GPIO_InitStruct.Pin = B1_Pin|BP3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : L0_Pin L1_Pin L2_Pin L3_Pin
                           L4_Pin L5_Pin L6_Pin L7_Pin */
  GPIO_InitStruct.Pin = L0_Pin|L1_Pin|L2_Pin|L3_Pin
                          |L4_Pin|L5_Pin|L6_Pin|L7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : SPI_CS_Pin */
  GPIO_InitStruct.Pin = SPI_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(SPI_CS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : BP1_Pin BP2_Pin */
  GPIO_InitStruct.Pin = BP1_Pin|BP2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
int __io_putchar(int ch){
	HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 0xFFFF);
	return ch;
}

float get_heading(void){
	IKS01A3_MOTION_SENSOR_GetAxes(IKS01A3_LIS2MDL_0, MOTION_MAGNETO, &mag_value);
	y=mag_value.y-y_offset;
	x=mag_value.x-x_offset;
	    float heading = atan2f((float)y,
	                           (float)x) * 180.0f / M_PI;

	    if (heading < 0)
	        heading += 360.0f;

	    return heading;

}


uint8_t get_led_count(float heading) {
    float diff = fabsf(heading - target_angle);
    if (diff > 180.0f) diff = 360.0f - diff;

    if      (diff <= 5.0f)   return 8;
    else if (diff <= 25.0f)  return 7;
    else if (diff <= 50.0f)  return 6;
    else if (diff <= 75.0f)  return 5;
    else if (diff <= 100.0f) return 4;
    else if (diff <= 120.0f) return 3;
    else if (diff <= 150.0f) return 2;
    else                     return 1;
}

void set_leds(uint8_t count) {
    HAL_GPIO_WritePin(L0_GPIO_Port, L0_Pin, (count > 0) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(L1_GPIO_Port, L1_Pin, (count > 1) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(L2_GPIO_Port, L2_Pin, (count > 2) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(L3_GPIO_Port, L3_Pin, (count > 3) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(L4_GPIO_Port, L4_Pin, (count > 4) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(L5_GPIO_Port, L5_Pin, (count > 5) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(L6_GPIO_Port, L6_Pin, (count > 6) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(L7_GPIO_Port, L7_Pin, (count > 7) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void show_angle(void) {
    float heading = get_heading();
    snprintf(str, sizeof(str), "%03.0f", heading);

    MAX7219_DisplayChar(1, str[0]);
    MAX7219_DisplayChar(2, str[1]);
    MAX7219_DisplayChar(3, str[2]);
    MAX7219_DisplayChar(4, 'o');

    if (state == GUESS_MODE) {
        set_leds(get_led_count(heading));
    } else {
        set_leds(0);
    }

    HAL_Delay(1000);
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == BP1_Pin)  // Afficher l'angle cible
    {
        target_angle = rand() % 361;
        char target_str[9];
        snprintf(target_str, sizeof(target_str), "%03d", target_angle);
//        MAX7219_DisplayChar(1, target_str[0]);
//        MAX7219_DisplayChar(2, target_str[1]);
//        MAX7219_DisplayChar(3, target_str[2]);
//        MAX7219_DisplayChar(4, 'C');  // C pour Cible
        printf("Angle cible: %d deg\r\n", target_angle);
        state = TARGET_GENERATED;
    }
    else if (GPIO_Pin == BP2_Pin)  // Activer mode visée
    {
        if (state == TARGET_GENERATED) {
            printf("Mode vise active\r\n");
            state = GUESS_MODE;
        }
    }
    else if (GPIO_Pin == BP3_Pin)  // Valider l'angle
    {
        if (state == GUESS_MODE) {
            float current = get_heading();
            snprintf(str, sizeof(str), "%03.0f", current); //La logique : tu lis l'angle, tu le formates dans str ensuite seulement tu utilises str pour afficher.
            printf("Angle actuel: %.1f\r\n", current);
            float diff = fabsf(current - target_angle);
            if (diff > 180) diff = 360 - diff;
            if (diff <= 5) {
                MAX7219_DisplayChar(1,'G');
                MAX7219_DisplayChar(2,str[1]);
                MAX7219_DisplayChar(3,str[2]);
                printf("BRAVO !!!\r\n");
            } else {
                printf("Rate (diff = %.1f deg)\r\n", diff);
            }
            state = TARGET_GENERATED;  // on garde le même angle !
        }
    }
}

//
//
//void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
//	  {
//	      if (GPIO_Pin == BP1_Pin)  // bouton user
//	      {
//	          if (state == WAIT_START)
//	          {
//	              target_angle = rand() % 361;
//	              printf("Angle cible: %d deg\r\n", target_angle);
//	              state = TARGET_GENERATED;
//	          }
//	          else if (state == TARGET_GENERATED)
//	          {
//	              printf("Mode vise active\r\n");
//	              state = GUESS_MODE;
//	          }
//	          else if (state == GUESS_MODE)
//	          {
//	              float current = get_heading();
//
//	              printf("Angle actuel: %.1f\r\n", current);
//
//	              float diff = fabsf(current - target_angle);
//
//	              if (diff > 180)
//	                  diff = 360 - diff;
//
//	              if (diff <= 5)
//	              {
//	            	  MAX7219_DisplayChar(1,'G');
//	            	  MAX7219_DisplayChar(2,str[1]);
//	            	  MAX7219_DisplayChar(3,str[2]);
//	                  printf("BRAVO !!!\r\n");
//	              }
//	              else
//	              {
//	                  printf("Rate (diff = %.1f deg)\r\n", diff);
//	              }
//
//	              state = WAIT_START;
//	          }
//	      }
//	  }


/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
