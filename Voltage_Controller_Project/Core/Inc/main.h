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
#include "stm32g4xx_hal.h"
#include "stm32g4xx_ll_adc.h"
#include "stm32g4xx_ll_comp.h"
#include "stm32g4xx_ll_exti.h"
#include "stm32g4xx_ll_dac.h"
#include "stm32g4xx_ll_dma.h"
#include "stm32g4xx_ll_hrtim.h"
#include "stm32g4xx_ll_rcc.h"
#include "stm32g4xx_ll_bus.h"
#include "stm32g4xx_ll_crs.h"
#include "stm32g4xx_ll_system.h"
#include "stm32g4xx_ll_cortex.h"
#include "stm32g4xx_ll_utils.h"
#include "stm32g4xx_ll_pwr.h"
#include "stm32g4xx_ll_ucpd.h"
#include "stm32g4xx_ll_usart.h"
#include "stm32g4xx_ll_gpio.h"

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
void MX_GPIO_Init(void);
void MX_DMA_Init(void);
void MX_ADC1_Init(void);
void MX_COMP2_Init(void);
void MX_COMP3_Init(void);
void MX_COMP4_Init(void);
void MX_COMP6_Init(void);
void MX_DAC1_Init(void);
void MX_DAC2_Init(void);
void MX_DAC3_Init(void);
void MX_HRTIM1_Init(void);
void MX_UCPD1_Init(void);
void MX_USART3_UART_Init(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define JOYSTICK_SEL_Pin LL_GPIO_PIN_13
#define JOYSTICK_SEL_GPIO_Port GPIOC
#define JOYSTICK_SEL_EXTI_IRQn EXTI15_10_IRQn
#define BUCKBOOST_LOAD_1_Pin LL_GPIO_PIN_14
#define BUCKBOOST_LOAD_1_GPIO_Port GPIOC
#define BUCKBOOST_LOAD_2_Pin LL_GPIO_PIN_15
#define BUCKBOOST_LOAD_2_GPIO_Port GPIOC
#define USBPD_VIN_Pin LL_GPIO_PIN_2
#define USBPD_VIN_GPIO_Port GPIOC
#define BUCKBOOST_USBPD_EN_Pin LL_GPIO_PIN_3
#define BUCKBOOST_USBPD_EN_GPIO_Port GPIOC
#define BUCK_GREEN_SENSE_Pin LL_GPIO_PIN_0
#define BUCK_GREEN_SENSE_GPIO_Port GPIOA
#define BUCKBOOST_VIN_Pin LL_GPIO_PIN_1
#define BUCKBOOST_VIN_GPIO_Port GPIOA
#define BUCKBOOST_I_IN_AVG_Pin LL_GPIO_PIN_2
#define BUCKBOOST_I_IN_AVG_GPIO_Port GPIOA
#define BUCKBOOST_VOUT_Pin LL_GPIO_PIN_3
#define BUCKBOOST_VOUT_GPIO_Port GPIOA
#define BUCK_RED_SENSE_Pin LL_GPIO_PIN_7
#define BUCK_RED_SENSE_GPIO_Port GPIOA
#define JOYSTICK_LEFT_Pin LL_GPIO_PIN_4
#define JOYSTICK_LEFT_GPIO_Port GPIOC
#define JOYSTICK_LEFT_EXTI_IRQn EXTI4_IRQn
#define JOYSTICK_DOWN_Pin LL_GPIO_PIN_5
#define JOYSTICK_DOWN_GPIO_Port GPIOC
#define JOYSTICK_DOWN_EXTI_IRQn EXTI9_5_IRQn
#define BUCK_BLUE_SENSE_Pin LL_GPIO_PIN_0
#define BUCK_BLUE_SENSE_GPIO_Port GPIOB
#define LD3_Pin LL_GPIO_PIN_1
#define LD3_GPIO_Port GPIOB
#define JOYSTICK_RIGHT_Pin LL_GPIO_PIN_2
#define JOYSTICK_RIGHT_GPIO_Port GPIOB
#define JOYSTICK_RIGHT_EXTI_IRQn EXTI2_IRQn
#define JOYSTICK_UP_Pin LL_GPIO_PIN_10
#define JOYSTICK_UP_GPIO_Port GPIOB
#define JOYSTICK_UP_EXTI_IRQn EXTI15_10_IRQn
#define BUCKBOOST_I_IN_SENSE_Pin LL_GPIO_PIN_11
#define BUCKBOOST_I_IN_SENSE_GPIO_Port GPIOB
#define BUCKBOOST_P1_DRIVE_Pin LL_GPIO_PIN_12
#define BUCKBOOST_P1_DRIVE_GPIO_Port GPIOB
#define BUCKBOOST_N1_DRIVE_Pin LL_GPIO_PIN_13
#define BUCKBOOST_N1_DRIVE_GPIO_Port GPIOB
#define BUCKBOOST_N2_DRIVE_Pin LL_GPIO_PIN_14
#define BUCKBOOST_N2_DRIVE_GPIO_Port GPIOB
#define BUCKBOOST_P2_DRIVE_Pin LL_GPIO_PIN_15
#define BUCKBOOST_P2_DRIVE_GPIO_Port GPIOB
#define BUCK_RED_DRIVE_Pin LL_GPIO_PIN_6
#define BUCK_RED_DRIVE_GPIO_Port GPIOC
#define RC_TP4_Pin LL_GPIO_PIN_7
#define RC_TP4_GPIO_Port GPIOC
#define BUCK_GREEN_DRIVE_Pin LL_GPIO_PIN_8
#define BUCK_GREEN_DRIVE_GPIO_Port GPIOC
#define BUCK_BLUE_DRIVE_Pin LL_GPIO_PIN_8
#define BUCK_BLUE_DRIVE_GPIO_Port GPIOA
#define LD2_Pin LL_GPIO_PIN_15
#define LD2_GPIO_Port GPIOA
#define USART3_TX_Pin LL_GPIO_PIN_10
#define USART3_TX_GPIO_Port GPIOC
#define USART3_RX_Pin LL_GPIO_PIN_11
#define USART3_RX_GPIO_Port GPIOC
#define USBPD_1A_PROTECT_Pin LL_GPIO_PIN_12
#define USBPD_1A_PROTECT_GPIO_Port GPIOC
#define USBPD_550mA_PROTECT_Pin LL_GPIO_PIN_2
#define USBPD_550mA_PROTECT_GPIO_Port GPIOD
#define LD5_Pin LL_GPIO_PIN_5
#define LD5_GPIO_Port GPIOB
#define LD4_Pin LL_GPIO_PIN_7
#define LD4_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
