/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define RADIO_NSS_Pin GPIO_PIN_15
#define RADIO_NSS_GPIO_Port GPIOA
#define RADIO_SCLK_Pin GPIO_PIN_3
#define RADIO_SCLK_GPIO_Port GPIOB
#define LD1_Pin GPIO_PIN_5
#define LD1_GPIO_Port GPIOB
#define RADIO_TCXO_VCC_Pin GPIO_PIN_12
#define RADIO_TCXO_VCC_GPIO_Port GPIOA
#define RADIO_DIO_0_Pin GPIO_PIN_4
#define RADIO_DIO_0_GPIO_Port GPIOB
#define RADIO_DIO_0_EXTI_IRQn EXTI4_15_IRQn
#define LD3_Pin GPIO_PIN_6
#define LD3_GPIO_Port GPIOB
#define RADIO_DIO_3_Pin GPIO_PIN_13
#define RADIO_DIO_3_GPIO_Port GPIOC
#define RADIO_DIO_3_EXTI_IRQn EXTI4_15_IRQn
#define LD4_Pin GPIO_PIN_7
#define LD4_GPIO_Port GPIOB
#define RADIO_ANT_SWITCH_TX_BOOST_Pin GPIO_PIN_1
#define RADIO_ANT_SWITCH_TX_BOOST_GPIO_Port GPIOC
#define RADIO_RESET_Pin GPIO_PIN_0
#define RADIO_RESET_GPIO_Port GPIOC
#define RADIO_DIO_1_Pin GPIO_PIN_1
#define RADIO_DIO_1_GPIO_Port GPIOB
#define RADIO_DIO_1_EXTI_IRQn EXTI0_1_IRQn
#define B1_Pin GPIO_PIN_2
#define B1_GPIO_Port GPIOB
#define RADIO_ANT_SWITCH_RX_Pin GPIO_PIN_1
#define RADIO_ANT_SWITCH_RX_GPIO_Port GPIOA
#define RADIO_ANT_SWITCH_TX_RFO_Pin GPIO_PIN_2
#define RADIO_ANT_SWITCH_TX_RFO_GPIO_Port GPIOC
#define RADIO_MOSI_Pin GPIO_PIN_7
#define RADIO_MOSI_GPIO_Port GPIOA
#define STLINK_RX_Pin GPIO_PIN_2
#define STLINK_RX_GPIO_Port GPIOA
#define RADIO_DIO_2_Pin GPIO_PIN_0
#define RADIO_DIO_2_GPIO_Port GPIOB
#define RADIO_DIO_2_EXTI_IRQn EXTI0_1_IRQn
#define RADIO_MISO_Pin GPIO_PIN_6
#define RADIO_MISO_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define STLINK_TX_Pin GPIO_PIN_3
#define STLINK_TX_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
