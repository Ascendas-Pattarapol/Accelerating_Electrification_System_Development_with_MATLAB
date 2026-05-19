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

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_4);
  while(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_4)
  {
  }
  LL_PWR_EnableRange1BoostMode();
  LL_RCC_HSI_Enable();
   /* Wait till HSI is ready */
  while(LL_RCC_HSI_IsReady() != 1)
  {
  }

  LL_RCC_HSI_SetCalibTrimming(64);
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI, LL_RCC_PLLM_DIV_4, 85, LL_RCC_PLLR_DIV_2);
  LL_RCC_PLL_EnableDomain_SYS();
  LL_RCC_PLL_Enable();
   /* Wait till PLL is ready */
  while(LL_RCC_PLL_IsReady() != 1)
  {
  }

  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_2);
   /* Wait till System clock is ready */
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {
  }

  /* Insure 1us transition state at intermediate medium speed clock*/
  for (__IO uint32_t i = (170 >> 1); i !=0; i--);

  /* Set AHB prescaler*/
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);
  LL_SetSystemCoreClock(170000000);

   /* Update the time base */
  if (HAL_InitTick (TICK_INT_PRIORITY) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  LL_ADC_InitTypeDef ADC_InitStruct = {0};
  LL_ADC_REG_InitTypeDef ADC_REG_InitStruct = {0};
  LL_ADC_CommonInitTypeDef ADC_CommonInitStruct = {0};

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  LL_RCC_SetADCClockSource(LL_RCC_ADC12_CLKSOURCE_SYSCLK);

  /* Peripheral clock enable */
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_ADC12);

  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOC);
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);
  /**ADC1 GPIO Configuration
  PC2   ------> ADC1_IN8
  PA1   ------> ADC1_IN2
  PA2   ------> ADC1_IN3
  PA3   ------> ADC1_IN4
  */
  GPIO_InitStruct.Pin = USBPD_VIN_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(USBPD_VIN_GPIO_Port, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = BUCKBOOST_VIN_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(BUCKBOOST_VIN_GPIO_Port, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = BUCKBOOST_I_IN_AVG_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(BUCKBOOST_I_IN_AVG_GPIO_Port, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = BUCKBOOST_VOUT_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(BUCKBOOST_VOUT_GPIO_Port, &GPIO_InitStruct);

  /* ADC1 interrupt Init */
  NVIC_SetPriority(ADC1_2_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
  NVIC_EnableIRQ(ADC1_2_IRQn);

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Common config
  */
  ADC_InitStruct.Resolution = LL_ADC_RESOLUTION_12B;
  ADC_InitStruct.DataAlignment = LL_ADC_DATA_ALIGN_RIGHT;
  ADC_InitStruct.LowPowerMode = LL_ADC_LP_MODE_NONE;
  LL_ADC_Init(ADC1, &ADC_InitStruct);
  ADC_REG_InitStruct.TriggerSource = LL_ADC_REG_TRIG_SOFTWARE;
  ADC_REG_InitStruct.SequencerLength = LL_ADC_REG_SEQ_SCAN_DISABLE;
  ADC_REG_InitStruct.SequencerDiscont = LL_ADC_REG_SEQ_DISCONT_DISABLE;
  ADC_REG_InitStruct.ContinuousMode = LL_ADC_REG_CONV_SINGLE;
  ADC_REG_InitStruct.DMATransfer = LL_ADC_REG_DMA_TRANSFER_NONE;
  ADC_REG_InitStruct.Overrun = LL_ADC_REG_OVR_DATA_PRESERVED;
  LL_ADC_REG_Init(ADC1, &ADC_REG_InitStruct);
  LL_ADC_SetGainCompensation(ADC1, 0);
  LL_ADC_SetOverSamplingScope(ADC1, LL_ADC_OVS_DISABLE);
  ADC_CommonInitStruct.CommonClock = LL_ADC_CLOCK_SYNC_PCLK_DIV4;
  ADC_CommonInitStruct.Multimode = LL_ADC_MULTI_INDEPENDENT;
  LL_ADC_CommonInit(__LL_ADC_COMMON_INSTANCE(ADC1), &ADC_CommonInitStruct);

  /* Disable ADC deep power down (enabled by default after reset state) */
  LL_ADC_DisableDeepPowerDown(ADC1);
  /* Enable ADC internal voltage regulator */
  LL_ADC_EnableInternalRegulator(ADC1);
  /* Delay for ADC internal voltage regulator stabilization. */
  /* Compute number of CPU cycles to wait for, from delay in us. */
  /* Note: Variable divided by 2 to compensate partially */
  /* CPU processing cycles (depends on compilation optimization). */
  /* Note: If system core clock frequency is below 200kHz, wait time */
  /* is only a few CPU processing cycles. */
  uint32_t wait_loop_index;
  wait_loop_index = ((LL_ADC_DELAY_INTERNAL_REGUL_STAB_US * (SystemCoreClock / (100000 * 2))) / 10);
  while(wait_loop_index != 0)
  {
    wait_loop_index--;
  }

  /** Configure Regular Channel
  */
  LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_1, LL_ADC_CHANNEL_8);
  LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_8, LL_ADC_SAMPLINGTIME_2CYCLES_5);
  LL_ADC_SetChannelSingleDiff(ADC1, LL_ADC_CHANNEL_8, LL_ADC_SINGLE_ENDED);
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief COMP2 Initialization Function
  * @param None
  * @retval None
  */
void MX_COMP2_Init(void)
{

  /* USER CODE BEGIN COMP2_Init 0 */

  /* USER CODE END COMP2_Init 0 */

  LL_COMP_InitTypeDef COMP_InitStruct = {0};

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);
  /**COMP2 GPIO Configuration
  PA7   ------> COMP2_INP
  */
  GPIO_InitStruct.Pin = BUCK_RED_SENSE_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(BUCK_RED_SENSE_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN COMP2_Init 1 */

  /* USER CODE END COMP2_Init 1 */
  COMP_InitStruct.InputPlus = LL_COMP_INPUT_PLUS_IO1;
  COMP_InitStruct.InputMinus = LL_COMP_INPUT_MINUS_DAC3_CH2;
  COMP_InitStruct.InputHysteresis = LL_COMP_HYSTERESIS_NONE;
  COMP_InitStruct.OutputPolarity = LL_COMP_OUTPUTPOL_NONINVERTED;
  COMP_InitStruct.OutputBlankingSource = LL_COMP_BLANKINGSRC_NONE;
  LL_COMP_Init(COMP2, &COMP_InitStruct);

  /* Wait loop initialization and execution */
  /* Note: Variable divided by 2 to compensate partially CPU processing cycles */
  __IO uint32_t wait_loop_index = 0;
  wait_loop_index = (LL_COMP_DELAY_VOLTAGE_SCALER_STAB_US * (SystemCoreClock / (1000000 * 2)));
  while(wait_loop_index != 0)
  {
    wait_loop_index--;
  }
  LL_EXTI_DisableEvent_0_31(LL_EXTI_LINE_22);
  LL_EXTI_DisableIT_0_31(LL_EXTI_LINE_22);
  /* USER CODE BEGIN COMP2_Init 2 */

  /* USER CODE END COMP2_Init 2 */

}

/**
  * @brief COMP3 Initialization Function
  * @param None
  * @retval None
  */
void MX_COMP3_Init(void)
{

  /* USER CODE BEGIN COMP3_Init 0 */

  /* USER CODE END COMP3_Init 0 */

  LL_COMP_InitTypeDef COMP_InitStruct = {0};

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);
  /**COMP3 GPIO Configuration
  PA0   ------> COMP3_INP
  */
  GPIO_InitStruct.Pin = BUCK_GREEN_SENSE_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(BUCK_GREEN_SENSE_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN COMP3_Init 1 */

  /* USER CODE END COMP3_Init 1 */
  COMP_InitStruct.InputPlus = LL_COMP_INPUT_PLUS_IO1;
  COMP_InitStruct.InputMinus = LL_COMP_INPUT_MINUS_DAC3_CH1;
  COMP_InitStruct.InputHysteresis = LL_COMP_HYSTERESIS_NONE;
  COMP_InitStruct.OutputPolarity = LL_COMP_OUTPUTPOL_NONINVERTED;
  COMP_InitStruct.OutputBlankingSource = LL_COMP_BLANKINGSRC_NONE;
  LL_COMP_Init(COMP3, &COMP_InitStruct);

  /* Wait loop initialization and execution */
  /* Note: Variable divided by 2 to compensate partially CPU processing cycles */
  __IO uint32_t wait_loop_index = 0;
  wait_loop_index = (LL_COMP_DELAY_VOLTAGE_SCALER_STAB_US * (SystemCoreClock / (1000000 * 2)));
  while(wait_loop_index != 0)
  {
    wait_loop_index--;
  }
  LL_EXTI_DisableEvent_0_31(LL_EXTI_LINE_29);
  LL_EXTI_DisableIT_0_31(LL_EXTI_LINE_29);
  /* USER CODE BEGIN COMP3_Init 2 */

  /* USER CODE END COMP3_Init 2 */

}

/**
  * @brief COMP4 Initialization Function
  * @param None
  * @retval None
  */
void MX_COMP4_Init(void)
{

  /* USER CODE BEGIN COMP4_Init 0 */

  /* USER CODE END COMP4_Init 0 */

  LL_COMP_InitTypeDef COMP_InitStruct = {0};

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);
  /**COMP4 GPIO Configuration
  PB0   ------> COMP4_INP
  */
  GPIO_InitStruct.Pin = BUCK_BLUE_SENSE_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(BUCK_BLUE_SENSE_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN COMP4_Init 1 */

  /* USER CODE END COMP4_Init 1 */
  COMP_InitStruct.InputPlus = LL_COMP_INPUT_PLUS_IO1;
  COMP_InitStruct.InputMinus = LL_COMP_INPUT_MINUS_DAC1_CH1;
  COMP_InitStruct.InputHysteresis = LL_COMP_HYSTERESIS_NONE;
  COMP_InitStruct.OutputPolarity = LL_COMP_OUTPUTPOL_NONINVERTED;
  COMP_InitStruct.OutputBlankingSource = LL_COMP_BLANKINGSRC_NONE;
  LL_COMP_Init(COMP4, &COMP_InitStruct);

  /* Wait loop initialization and execution */
  /* Note: Variable divided by 2 to compensate partially CPU processing cycles */
  __IO uint32_t wait_loop_index = 0;
  wait_loop_index = (LL_COMP_DELAY_VOLTAGE_SCALER_STAB_US * (SystemCoreClock / (1000000 * 2)));
  while(wait_loop_index != 0)
  {
    wait_loop_index--;
  }
  LL_EXTI_DisableEvent_0_31(LL_EXTI_LINE_30);
  LL_EXTI_DisableIT_0_31(LL_EXTI_LINE_30);
  /* USER CODE BEGIN COMP4_Init 2 */

  /* USER CODE END COMP4_Init 2 */

}

/**
  * @brief COMP6 Initialization Function
  * @param None
  * @retval None
  */
void MX_COMP6_Init(void)
{

  /* USER CODE BEGIN COMP6_Init 0 */

  /* USER CODE END COMP6_Init 0 */

  LL_COMP_InitTypeDef COMP_InitStruct = {0};

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);
  /**COMP6 GPIO Configuration
  PB11   ------> COMP6_INP
  */
  GPIO_InitStruct.Pin = BUCKBOOST_I_IN_SENSE_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(BUCKBOOST_I_IN_SENSE_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN COMP6_Init 1 */

  /* USER CODE END COMP6_Init 1 */
  COMP_InitStruct.InputPlus = LL_COMP_INPUT_PLUS_IO1;
  COMP_InitStruct.InputMinus = LL_COMP_INPUT_MINUS_DAC2_CH1;
  COMP_InitStruct.InputHysteresis = LL_COMP_HYSTERESIS_NONE;
  COMP_InitStruct.OutputPolarity = LL_COMP_OUTPUTPOL_NONINVERTED;
  COMP_InitStruct.OutputBlankingSource = LL_COMP_BLANKINGSRC_NONE;
  LL_COMP_Init(COMP6, &COMP_InitStruct);

  /* Wait loop initialization and execution */
  /* Note: Variable divided by 2 to compensate partially CPU processing cycles */
  __IO uint32_t wait_loop_index = 0;
  wait_loop_index = (LL_COMP_DELAY_VOLTAGE_SCALER_STAB_US * (SystemCoreClock / (1000000 * 2)));
  while(wait_loop_index != 0)
  {
    wait_loop_index--;
  }
  LL_EXTI_DisableEvent_32_63(LL_EXTI_LINE_32);
  LL_EXTI_DisableIT_32_63(LL_EXTI_LINE_32);
  /* USER CODE BEGIN COMP6_Init 2 */

  /* USER CODE END COMP6_Init 2 */

}

/**
  * @brief DAC1 Initialization Function
  * @param None
  * @retval None
  */
void MX_DAC1_Init(void)
{

  /* USER CODE BEGIN DAC1_Init 0 */

  /* USER CODE END DAC1_Init 0 */

  LL_DAC_InitTypeDef DAC_InitStruct = {0};

  /* Peripheral clock enable */
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_DAC1);

  /* USER CODE BEGIN DAC1_Init 1 */

  /* USER CODE END DAC1_Init 1 */

  /** DAC channel OUT1 config
  */
  LL_DAC_SetSignedFormat(DAC1, LL_DAC_CHANNEL_1, LL_DAC_SIGNED_FORMAT_DISABLE);
  DAC_InitStruct.TriggerSource = LL_DAC_TRIG_SOFTWARE;
  DAC_InitStruct.TriggerSource2 = LL_DAC_TRIG_SOFTWARE;
  DAC_InitStruct.WaveAutoGeneration = LL_DAC_WAVE_AUTO_GENERATION_NONE;
  DAC_InitStruct.OutputBuffer = LL_DAC_OUTPUT_BUFFER_DISABLE;
  DAC_InitStruct.OutputConnection = LL_DAC_OUTPUT_CONNECT_INTERNAL;
  DAC_InitStruct.OutputMode = LL_DAC_OUTPUT_MODE_NORMAL;
  LL_DAC_Init(DAC1, LL_DAC_CHANNEL_1, &DAC_InitStruct);
  LL_DAC_DisableTrigger(DAC1, LL_DAC_CHANNEL_1);
  LL_DAC_DisableDMADoubleDataMode(DAC1, LL_DAC_CHANNEL_1);
  /* USER CODE BEGIN DAC1_Init 2 */

  /* USER CODE END DAC1_Init 2 */

}

/**
  * @brief DAC2 Initialization Function
  * @param None
  * @retval None
  */
void MX_DAC2_Init(void)
{

  /* USER CODE BEGIN DAC2_Init 0 */

  /* USER CODE END DAC2_Init 0 */

  LL_DAC_InitTypeDef DAC_InitStruct = {0};

  /* Peripheral clock enable */
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_DAC2);

  /* USER CODE BEGIN DAC2_Init 1 */

  /* USER CODE END DAC2_Init 1 */

  /** DAC channel OUT1 config
  */
  LL_DAC_SetSignedFormat(DAC2, LL_DAC_CHANNEL_1, LL_DAC_SIGNED_FORMAT_DISABLE);
  DAC_InitStruct.TriggerSource = LL_DAC_TRIG_SOFTWARE;
  DAC_InitStruct.TriggerSource2 = LL_DAC_TRIG_SOFTWARE;
  DAC_InitStruct.WaveAutoGeneration = LL_DAC_WAVE_AUTO_GENERATION_NONE;
  DAC_InitStruct.OutputBuffer = LL_DAC_OUTPUT_BUFFER_DISABLE;
  DAC_InitStruct.OutputConnection = LL_DAC_OUTPUT_CONNECT_INTERNAL;
  DAC_InitStruct.OutputMode = LL_DAC_OUTPUT_MODE_NORMAL;
  LL_DAC_Init(DAC2, LL_DAC_CHANNEL_1, &DAC_InitStruct);
  LL_DAC_DisableTrigger(DAC2, LL_DAC_CHANNEL_1);
  LL_DAC_DisableDMADoubleDataMode(DAC2, LL_DAC_CHANNEL_1);
  /* USER CODE BEGIN DAC2_Init 2 */

  /* USER CODE END DAC2_Init 2 */

}

/**
  * @brief DAC3 Initialization Function
  * @param None
  * @retval None
  */
void MX_DAC3_Init(void)
{

  /* USER CODE BEGIN DAC3_Init 0 */

  /* USER CODE END DAC3_Init 0 */

  LL_DAC_InitTypeDef DAC_InitStruct = {0};

  /* Peripheral clock enable */
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_DAC3);

  /* USER CODE BEGIN DAC3_Init 1 */

  /* USER CODE END DAC3_Init 1 */

  /** DAC channel OUT1 config
  */
  LL_DAC_SetSignedFormat(DAC3, LL_DAC_CHANNEL_1, LL_DAC_SIGNED_FORMAT_DISABLE);
  DAC_InitStruct.TriggerSource = LL_DAC_TRIG_SOFTWARE;
  DAC_InitStruct.TriggerSource2 = LL_DAC_TRIG_SOFTWARE;
  DAC_InitStruct.WaveAutoGeneration = LL_DAC_WAVE_AUTO_GENERATION_NONE;
  DAC_InitStruct.OutputBuffer = LL_DAC_OUTPUT_BUFFER_DISABLE;
  DAC_InitStruct.OutputConnection = LL_DAC_OUTPUT_CONNECT_INTERNAL;
  DAC_InitStruct.OutputMode = LL_DAC_OUTPUT_MODE_NORMAL;
  LL_DAC_Init(DAC3, LL_DAC_CHANNEL_1, &DAC_InitStruct);
  LL_DAC_DisableTrigger(DAC3, LL_DAC_CHANNEL_1);
  LL_DAC_DisableDMADoubleDataMode(DAC3, LL_DAC_CHANNEL_1);

  /** DAC channel OUT2 config
  */
  LL_DAC_SetSignedFormat(DAC3, LL_DAC_CHANNEL_2, LL_DAC_SIGNED_FORMAT_DISABLE);
  LL_DAC_Init(DAC3, LL_DAC_CHANNEL_2, &DAC_InitStruct);
  LL_DAC_DisableTrigger(DAC3, LL_DAC_CHANNEL_2);
  LL_DAC_DisableDMADoubleDataMode(DAC3, LL_DAC_CHANNEL_2);
  /* USER CODE BEGIN DAC3_Init 2 */

  /* USER CODE END DAC3_Init 2 */

}

/**
  * @brief HRTIM1 Initialization Function
  * @param None
  * @retval None
  */
void MX_HRTIM1_Init(void)
{

  /* USER CODE BEGIN HRTIM1_Init 0 */

  /* USER CODE END HRTIM1_Init 0 */

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* Peripheral clock enable */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_HRTIM1);

  /* HRTIM1 interrupt Init */
  NVIC_SetPriority(HRTIM1_Master_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
  NVIC_EnableIRQ(HRTIM1_Master_IRQn);
  NVIC_SetPriority(HRTIM1_TIMF_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
  NVIC_EnableIRQ(HRTIM1_TIMF_IRQn);

  /* USER CODE BEGIN HRTIM1_Init 1 */

  /* USER CODE END HRTIM1_Init 1 */
  LL_HRTIM_ConfigDLLCalibration(HRTIM1, LL_HRTIM_DLLCALIBRATION_MODE_CONTINUOUS, LL_HRTIM_DLLCALIBRATION_RATE_3);

  /* Poll for DLL end of calibration */
#if (USE_TIMEOUT == 1)
  uint32_t Timeout = 10; /* Timeout Initialization */
#endif  /*USE_TIMEOUT*/

  while(LL_HRTIM_IsActiveFlag_DLLRDY(HRTIM1) == RESET){
#if (USE_TIMEOUT == 1)
    if (LL_SYSTICK_IsActiveCounterFlag())  /* Check Systick counter flag to decrement the time-out value */
    {
        if(Timeout-- == 0)
        {
          Error_Handler();  /* error management */
        }
    }
#endif  /* USE_TIMEOUT */
  }

  LL_HRTIM_TIM_SetPrescaler(HRTIM1, LL_HRTIM_TIMER_A, LL_HRTIM_PRESCALERRATIO_MUL32);
  LL_HRTIM_TIM_SetCounterMode(HRTIM1, LL_HRTIM_TIMER_A, LL_HRTIM_MODE_CONTINUOUS);
  LL_HRTIM_TIM_SetPeriod(HRTIM1, LL_HRTIM_TIMER_A, 0xFFDF);
  LL_HRTIM_TIM_SetRepetition(HRTIM1, LL_HRTIM_TIMER_A, 0x00);
  LL_HRTIM_TIM_SetUpdateGating(HRTIM1, LL_HRTIM_TIMER_A, LL_HRTIM_UPDATEGATING_INDEPENDENT);
  LL_HRTIM_TIM_SetCountingMode(HRTIM1, LL_HRTIM_TIMER_A, LL_HRTIM_COUNTING_MODE_UP);
  LL_HRTIM_TIM_SetDACTrig(HRTIM1, LL_HRTIM_TIMER_A, LL_HRTIM_DACTRIG_NONE);
  LL_HRTIM_TIM_DisableHalfMode(HRTIM1, LL_HRTIM_TIMER_A);
  LL_HRTIM_TIM_SetInterleavedMode(HRTIM1, LL_HRTIM_TIMER_A, LL_HRTIM_INTERLEAVED_MODE_DISABLED);
  LL_HRTIM_TIM_DisableStartOnSync(HRTIM1, LL_HRTIM_TIMER_A);
  LL_HRTIM_TIM_DisableResetOnSync(HRTIM1, LL_HRTIM_TIMER_A);
  LL_HRTIM_TIM_DisablePreload(HRTIM1, LL_HRTIM_TIMER_A);
  LL_HRTIM_TIM_SetUpdateTrig(HRTIM1, LL_HRTIM_TIMER_A, LL_HRTIM_UPDATETRIG_NONE|LL_HRTIM_UPDATETRIG_NONE);
  LL_HRTIM_TIM_SetResetTrig(HRTIM1, LL_HRTIM_TIMER_A, LL_HRTIM_RESETTRIG_NONE);
  LL_HRTIM_TIM_DisablePushPullMode(HRTIM1, LL_HRTIM_TIMER_A);
  LL_HRTIM_TIM_DisableDeadTime(HRTIM1, LL_HRTIM_TIMER_A);
  LL_HRTIM_TIM_SetBurstModeOption(HRTIM1, LL_HRTIM_TIMER_A, LL_HRTIM_BURSTMODE_MAINTAINCLOCK);
  LL_HRTIM_ForceUpdate(HRTIM1, LL_HRTIM_TIMER_A);
  LL_HRTIM_TIM_DisableResyncUpdate(HRTIM1, LL_HRTIM_TIMER_A);
  LL_HRTIM_OUT_SetPolarity(HRTIM1, LL_HRTIM_OUTPUT_TA1, LL_HRTIM_OUT_POSITIVE_POLARITY);
  LL_HRTIM_OUT_SetOutputSetSrc(HRTIM1, LL_HRTIM_OUTPUT_TA1, LL_HRTIM_OUTPUTSET_NONE);
  LL_HRTIM_OUT_SetOutputResetSrc(HRTIM1, LL_HRTIM_OUTPUT_TA1, LL_HRTIM_OUTPUTRESET_NONE);
  LL_HRTIM_OUT_SetIdleMode(HRTIM1, LL_HRTIM_OUTPUT_TA1, LL_HRTIM_OUT_NO_IDLE);
  LL_HRTIM_OUT_SetIdleLevel(HRTIM1, LL_HRTIM_OUTPUT_TA1, LL_HRTIM_OUT_IDLELEVEL_INACTIVE);
  LL_HRTIM_OUT_SetFaultState(HRTIM1, LL_HRTIM_OUTPUT_TA1, LL_HRTIM_OUT_FAULTSTATE_NO_ACTION);
  LL_HRTIM_OUT_SetChopperMode(HRTIM1, LL_HRTIM_OUTPUT_TA1, LL_HRTIM_OUT_CHOPPERMODE_DISABLED);

  /* Poll for DLL end of calibration */
#if (USE_TIMEOUT == 1)
  uint32_t Timeout = 10; /* Timeout Initialization */
#endif  /*USE_TIMEOUT*/

  while(LL_HRTIM_IsActiveFlag_DLLRDY(HRTIM1) == RESET){
#if (USE_TIMEOUT == 1)
    if (LL_SYSTICK_IsActiveCounterFlag())  /* Check Systick counter flag to decrement the time-out value */
    {
        if(Timeout-- == 0)
        {
          Error_Handler();  /* error management */
        }
    }
#endif  /* USE_TIMEOUT */
  }

  LL_HRTIM_TIM_SetPrescaler(HRTIM1, LL_HRTIM_TIMER_C, LL_HRTIM_PRESCALERRATIO_MUL32);
  LL_HRTIM_TIM_SetCounterMode(HRTIM1, LL_HRTIM_TIMER_C, LL_HRTIM_MODE_CONTINUOUS);
  LL_HRTIM_TIM_SetPeriod(HRTIM1, LL_HRTIM_TIMER_C, 0xFFDF);
  LL_HRTIM_TIM_SetRepetition(HRTIM1, LL_HRTIM_TIMER_C, 0x00);
  LL_HRTIM_TIM_SetUpdateGating(HRTIM1, LL_HRTIM_TIMER_C, LL_HRTIM_UPDATEGATING_INDEPENDENT);
  LL_HRTIM_TIM_SetCountingMode(HRTIM1, LL_HRTIM_TIMER_C, LL_HRTIM_COUNTING_MODE_UP);
  LL_HRTIM_TIM_SetDACTrig(HRTIM1, LL_HRTIM_TIMER_C, LL_HRTIM_DACTRIG_NONE);
  LL_HRTIM_TIM_DisableHalfMode(HRTIM1, LL_HRTIM_TIMER_C);
  LL_HRTIM_TIM_SetInterleavedMode(HRTIM1, LL_HRTIM_TIMER_C, LL_HRTIM_INTERLEAVED_MODE_DISABLED);
  LL_HRTIM_TIM_DisableStartOnSync(HRTIM1, LL_HRTIM_TIMER_C);
  LL_HRTIM_TIM_DisableResetOnSync(HRTIM1, LL_HRTIM_TIMER_C);
  LL_HRTIM_TIM_DisablePreload(HRTIM1, LL_HRTIM_TIMER_C);
  LL_HRTIM_TIM_SetUpdateTrig(HRTIM1, LL_HRTIM_TIMER_C, LL_HRTIM_UPDATETRIG_NONE|LL_HRTIM_UPDATETRIG_NONE);
  LL_HRTIM_TIM_SetResetTrig(HRTIM1, LL_HRTIM_TIMER_C, LL_HRTIM_RESETTRIG_NONE);
  LL_HRTIM_TIM_DisablePushPullMode(HRTIM1, LL_HRTIM_TIMER_C);
  LL_HRTIM_TIM_DisableDeadTime(HRTIM1, LL_HRTIM_TIMER_C);
  LL_HRTIM_TIM_SetBurstModeOption(HRTIM1, LL_HRTIM_TIMER_C, LL_HRTIM_BURSTMODE_MAINTAINCLOCK);
  LL_HRTIM_ForceUpdate(HRTIM1, LL_HRTIM_TIMER_C);
  LL_HRTIM_TIM_DisableResyncUpdate(HRTIM1, LL_HRTIM_TIMER_C);
  LL_HRTIM_OUT_SetPolarity(HRTIM1, LL_HRTIM_OUTPUT_TC1, LL_HRTIM_OUT_POSITIVE_POLARITY);
  LL_HRTIM_OUT_SetOutputSetSrc(HRTIM1, LL_HRTIM_OUTPUT_TC1, LL_HRTIM_OUTPUTSET_NONE);
  LL_HRTIM_OUT_SetOutputResetSrc(HRTIM1, LL_HRTIM_OUTPUT_TC1, LL_HRTIM_OUTPUTRESET_NONE);
  LL_HRTIM_OUT_SetIdleMode(HRTIM1, LL_HRTIM_OUTPUT_TC1, LL_HRTIM_OUT_NO_IDLE);
  LL_HRTIM_OUT_SetIdleLevel(HRTIM1, LL_HRTIM_OUTPUT_TC1, LL_HRTIM_OUT_IDLELEVEL_INACTIVE);
  LL_HRTIM_OUT_SetFaultState(HRTIM1, LL_HRTIM_OUTPUT_TC1, LL_HRTIM_OUT_FAULTSTATE_NO_ACTION);
  LL_HRTIM_OUT_SetChopperMode(HRTIM1, LL_HRTIM_OUTPUT_TC1, LL_HRTIM_OUT_CHOPPERMODE_DISABLED);
  LL_HRTIM_OUT_SetPolarity(HRTIM1, LL_HRTIM_OUTPUT_TC2, LL_HRTIM_OUT_POSITIVE_POLARITY);
  LL_HRTIM_OUT_SetOutputSetSrc(HRTIM1, LL_HRTIM_OUTPUT_TC2, LL_HRTIM_OUTPUTSET_NONE);
  LL_HRTIM_OUT_SetOutputResetSrc(HRTIM1, LL_HRTIM_OUTPUT_TC2, LL_HRTIM_OUTPUTRESET_NONE);
  LL_HRTIM_OUT_SetIdleMode(HRTIM1, LL_HRTIM_OUTPUT_TC2, LL_HRTIM_OUT_NO_IDLE);
  LL_HRTIM_OUT_SetIdleLevel(HRTIM1, LL_HRTIM_OUTPUT_TC2, LL_HRTIM_OUT_IDLELEVEL_INACTIVE);
  LL_HRTIM_OUT_SetFaultState(HRTIM1, LL_HRTIM_OUTPUT_TC2, LL_HRTIM_OUT_FAULTSTATE_NO_ACTION);
  LL_HRTIM_OUT_SetChopperMode(HRTIM1, LL_HRTIM_OUTPUT_TC2, LL_HRTIM_OUT_CHOPPERMODE_DISABLED);

  /* Poll for DLL end of calibration */
#if (USE_TIMEOUT == 1)
  uint32_t Timeout = 10; /* Timeout Initialization */
#endif  /*USE_TIMEOUT*/

  while(LL_HRTIM_IsActiveFlag_DLLRDY(HRTIM1) == RESET){
#if (USE_TIMEOUT == 1)
    if (LL_SYSTICK_IsActiveCounterFlag())  /* Check Systick counter flag to decrement the time-out value */
    {
        if(Timeout-- == 0)
        {
          Error_Handler();  /* error management */
        }
    }
#endif  /* USE_TIMEOUT */
  }

  LL_HRTIM_TIM_SetPrescaler(HRTIM1, LL_HRTIM_TIMER_D, LL_HRTIM_PRESCALERRATIO_MUL32);
  LL_HRTIM_TIM_SetCounterMode(HRTIM1, LL_HRTIM_TIMER_D, LL_HRTIM_MODE_CONTINUOUS);
  LL_HRTIM_TIM_SetPeriod(HRTIM1, LL_HRTIM_TIMER_D, 0xFFDF);
  LL_HRTIM_TIM_SetRepetition(HRTIM1, LL_HRTIM_TIMER_D, 0x00);
  LL_HRTIM_TIM_SetUpdateGating(HRTIM1, LL_HRTIM_TIMER_D, LL_HRTIM_UPDATEGATING_INDEPENDENT);
  LL_HRTIM_TIM_SetCountingMode(HRTIM1, LL_HRTIM_TIMER_D, LL_HRTIM_COUNTING_MODE_UP);
  LL_HRTIM_TIM_SetDACTrig(HRTIM1, LL_HRTIM_TIMER_D, LL_HRTIM_DACTRIG_NONE);
  LL_HRTIM_TIM_DisableHalfMode(HRTIM1, LL_HRTIM_TIMER_D);
  LL_HRTIM_TIM_SetInterleavedMode(HRTIM1, LL_HRTIM_TIMER_D, LL_HRTIM_INTERLEAVED_MODE_DISABLED);
  LL_HRTIM_TIM_DisableStartOnSync(HRTIM1, LL_HRTIM_TIMER_D);
  LL_HRTIM_TIM_DisableResetOnSync(HRTIM1, LL_HRTIM_TIMER_D);
  LL_HRTIM_TIM_DisablePreload(HRTIM1, LL_HRTIM_TIMER_D);
  LL_HRTIM_TIM_SetUpdateTrig(HRTIM1, LL_HRTIM_TIMER_D, LL_HRTIM_UPDATETRIG_NONE|LL_HRTIM_UPDATETRIG_NONE);
  LL_HRTIM_TIM_SetResetTrig(HRTIM1, LL_HRTIM_TIMER_D, LL_HRTIM_RESETTRIG_NONE);
  LL_HRTIM_TIM_DisablePushPullMode(HRTIM1, LL_HRTIM_TIMER_D);
  LL_HRTIM_TIM_DisableDeadTime(HRTIM1, LL_HRTIM_TIMER_D);
  LL_HRTIM_TIM_SetBurstModeOption(HRTIM1, LL_HRTIM_TIMER_D, LL_HRTIM_BURSTMODE_MAINTAINCLOCK);
  LL_HRTIM_ForceUpdate(HRTIM1, LL_HRTIM_TIMER_D);
  LL_HRTIM_TIM_DisableResyncUpdate(HRTIM1, LL_HRTIM_TIMER_D);
  LL_HRTIM_OUT_SetPolarity(HRTIM1, LL_HRTIM_OUTPUT_TD1, LL_HRTIM_OUT_POSITIVE_POLARITY);
  LL_HRTIM_OUT_SetOutputSetSrc(HRTIM1, LL_HRTIM_OUTPUT_TD1, LL_HRTIM_OUTPUTSET_NONE);
  LL_HRTIM_OUT_SetOutputResetSrc(HRTIM1, LL_HRTIM_OUTPUT_TD1, LL_HRTIM_OUTPUTRESET_NONE);
  LL_HRTIM_OUT_SetIdleMode(HRTIM1, LL_HRTIM_OUTPUT_TD1, LL_HRTIM_OUT_NO_IDLE);
  LL_HRTIM_OUT_SetIdleLevel(HRTIM1, LL_HRTIM_OUTPUT_TD1, LL_HRTIM_OUT_IDLELEVEL_INACTIVE);
  LL_HRTIM_OUT_SetFaultState(HRTIM1, LL_HRTIM_OUTPUT_TD1, LL_HRTIM_OUT_FAULTSTATE_NO_ACTION);
  LL_HRTIM_OUT_SetChopperMode(HRTIM1, LL_HRTIM_OUTPUT_TD1, LL_HRTIM_OUT_CHOPPERMODE_DISABLED);
  LL_HRTIM_OUT_SetPolarity(HRTIM1, LL_HRTIM_OUTPUT_TD2, LL_HRTIM_OUT_POSITIVE_POLARITY);
  LL_HRTIM_OUT_SetOutputSetSrc(HRTIM1, LL_HRTIM_OUTPUT_TD2, LL_HRTIM_OUTPUTSET_NONE);
  LL_HRTIM_OUT_SetOutputResetSrc(HRTIM1, LL_HRTIM_OUTPUT_TD2, LL_HRTIM_OUTPUTRESET_NONE);
  LL_HRTIM_OUT_SetIdleMode(HRTIM1, LL_HRTIM_OUTPUT_TD2, LL_HRTIM_OUT_NO_IDLE);
  LL_HRTIM_OUT_SetIdleLevel(HRTIM1, LL_HRTIM_OUTPUT_TD2, LL_HRTIM_OUT_IDLELEVEL_INACTIVE);
  LL_HRTIM_OUT_SetFaultState(HRTIM1, LL_HRTIM_OUTPUT_TD2, LL_HRTIM_OUT_FAULTSTATE_NO_ACTION);
  LL_HRTIM_OUT_SetChopperMode(HRTIM1, LL_HRTIM_OUTPUT_TD2, LL_HRTIM_OUT_CHOPPERMODE_DISABLED);

  /* Poll for DLL end of calibration */
#if (USE_TIMEOUT == 1)
  uint32_t Timeout = 10; /* Timeout Initialization */
#endif  /*USE_TIMEOUT*/

  while(LL_HRTIM_IsActiveFlag_DLLRDY(HRTIM1) == RESET){
#if (USE_TIMEOUT == 1)
    if (LL_SYSTICK_IsActiveCounterFlag())  /* Check Systick counter flag to decrement the time-out value */
    {
        if(Timeout-- == 0)
        {
          Error_Handler();  /* error management */
        }
    }
#endif  /* USE_TIMEOUT */
  }

  LL_HRTIM_TIM_SetPrescaler(HRTIM1, LL_HRTIM_TIMER_E, LL_HRTIM_PRESCALERRATIO_MUL32);
  LL_HRTIM_TIM_SetCounterMode(HRTIM1, LL_HRTIM_TIMER_E, LL_HRTIM_MODE_CONTINUOUS);
  LL_HRTIM_TIM_SetPeriod(HRTIM1, LL_HRTIM_TIMER_E, 0xFFDF);
  LL_HRTIM_TIM_SetRepetition(HRTIM1, LL_HRTIM_TIMER_E, 0x00);
  LL_HRTIM_TIM_SetUpdateGating(HRTIM1, LL_HRTIM_TIMER_E, LL_HRTIM_UPDATEGATING_INDEPENDENT);
  LL_HRTIM_TIM_SetCountingMode(HRTIM1, LL_HRTIM_TIMER_E, LL_HRTIM_COUNTING_MODE_UP);
  LL_HRTIM_TIM_SetDACTrig(HRTIM1, LL_HRTIM_TIMER_E, LL_HRTIM_DACTRIG_NONE);
  LL_HRTIM_TIM_DisableHalfMode(HRTIM1, LL_HRTIM_TIMER_E);
  LL_HRTIM_TIM_SetInterleavedMode(HRTIM1, LL_HRTIM_TIMER_E, LL_HRTIM_INTERLEAVED_MODE_DISABLED);
  LL_HRTIM_TIM_DisableStartOnSync(HRTIM1, LL_HRTIM_TIMER_E);
  LL_HRTIM_TIM_DisableResetOnSync(HRTIM1, LL_HRTIM_TIMER_E);
  LL_HRTIM_TIM_DisablePreload(HRTIM1, LL_HRTIM_TIMER_E);
  LL_HRTIM_TIM_SetUpdateTrig(HRTIM1, LL_HRTIM_TIMER_E, LL_HRTIM_UPDATETRIG_NONE|LL_HRTIM_UPDATETRIG_NONE);
  LL_HRTIM_TIM_SetResetTrig(HRTIM1, LL_HRTIM_TIMER_E, LL_HRTIM_RESETTRIG_NONE);
  LL_HRTIM_TIM_DisablePushPullMode(HRTIM1, LL_HRTIM_TIMER_E);
  LL_HRTIM_TIM_DisableDeadTime(HRTIM1, LL_HRTIM_TIMER_E);
  LL_HRTIM_TIM_SetBurstModeOption(HRTIM1, LL_HRTIM_TIMER_E, LL_HRTIM_BURSTMODE_MAINTAINCLOCK);
  LL_HRTIM_ForceUpdate(HRTIM1, LL_HRTIM_TIMER_E);
  LL_HRTIM_TIM_DisableResyncUpdate(HRTIM1, LL_HRTIM_TIMER_E);
  LL_HRTIM_OUT_SetPolarity(HRTIM1, LL_HRTIM_OUTPUT_TE1, LL_HRTIM_OUT_POSITIVE_POLARITY);
  LL_HRTIM_OUT_SetOutputSetSrc(HRTIM1, LL_HRTIM_OUTPUT_TE1, LL_HRTIM_OUTPUTSET_NONE);
  LL_HRTIM_OUT_SetOutputResetSrc(HRTIM1, LL_HRTIM_OUTPUT_TE1, LL_HRTIM_OUTPUTRESET_NONE);
  LL_HRTIM_OUT_SetIdleMode(HRTIM1, LL_HRTIM_OUTPUT_TE1, LL_HRTIM_OUT_NO_IDLE);
  LL_HRTIM_OUT_SetIdleLevel(HRTIM1, LL_HRTIM_OUTPUT_TE1, LL_HRTIM_OUT_IDLELEVEL_INACTIVE);
  LL_HRTIM_OUT_SetFaultState(HRTIM1, LL_HRTIM_OUTPUT_TE1, LL_HRTIM_OUT_FAULTSTATE_NO_ACTION);
  LL_HRTIM_OUT_SetChopperMode(HRTIM1, LL_HRTIM_OUTPUT_TE1, LL_HRTIM_OUT_CHOPPERMODE_DISABLED);

  /* Poll for DLL end of calibration */
#if (USE_TIMEOUT == 1)
  uint32_t Timeout = 10; /* Timeout Initialization */
#endif  /*USE_TIMEOUT*/

  while(LL_HRTIM_IsActiveFlag_DLLRDY(HRTIM1) == RESET){
#if (USE_TIMEOUT == 1)
    if (LL_SYSTICK_IsActiveCounterFlag())  /* Check Systick counter flag to decrement the time-out value */
    {
        if(Timeout-- == 0)
        {
          Error_Handler();  /* error management */
        }
    }
#endif  /* USE_TIMEOUT */
  }

  LL_HRTIM_TIM_SetPrescaler(HRTIM1, LL_HRTIM_TIMER_F, LL_HRTIM_PRESCALERRATIO_MUL32);
  LL_HRTIM_TIM_SetCounterMode(HRTIM1, LL_HRTIM_TIMER_F, LL_HRTIM_MODE_CONTINUOUS);
  LL_HRTIM_TIM_SetPeriod(HRTIM1, LL_HRTIM_TIMER_F, 0xFFDF);
  LL_HRTIM_TIM_SetRepetition(HRTIM1, LL_HRTIM_TIMER_F, 0x00);
  LL_HRTIM_TIM_SetUpdateGating(HRTIM1, LL_HRTIM_TIMER_F, LL_HRTIM_UPDATEGATING_INDEPENDENT);
  LL_HRTIM_TIM_SetCountingMode(HRTIM1, LL_HRTIM_TIMER_F, LL_HRTIM_COUNTING_MODE_UP);
  LL_HRTIM_TIM_SetDACTrig(HRTIM1, LL_HRTIM_TIMER_F, LL_HRTIM_DACTRIG_NONE);
  LL_HRTIM_TIM_DisableHalfMode(HRTIM1, LL_HRTIM_TIMER_F);
  LL_HRTIM_TIM_SetInterleavedMode(HRTIM1, LL_HRTIM_TIMER_F, LL_HRTIM_INTERLEAVED_MODE_DISABLED);
  LL_HRTIM_TIM_DisableStartOnSync(HRTIM1, LL_HRTIM_TIMER_F);
  LL_HRTIM_TIM_DisableResetOnSync(HRTIM1, LL_HRTIM_TIMER_F);
  LL_HRTIM_TIM_DisablePreload(HRTIM1, LL_HRTIM_TIMER_F);
  LL_HRTIM_TIM_SetUpdateTrig(HRTIM1, LL_HRTIM_TIMER_F, LL_HRTIM_UPDATETRIG_NONE|LL_HRTIM_UPDATETRIG_NONE);
  LL_HRTIM_TIM_SetResetTrig(HRTIM1, LL_HRTIM_TIMER_F, LL_HRTIM_RESETTRIG_NONE);
  LL_HRTIM_TIM_DisablePushPullMode(HRTIM1, LL_HRTIM_TIMER_F);
  LL_HRTIM_TIM_DisableDeadTime(HRTIM1, LL_HRTIM_TIMER_F);
  LL_HRTIM_TIM_EnableDLYPRT(HRTIM1, LL_HRTIM_TIMER_F);
  LL_HRTIM_TIM_SetBurstModeOption(HRTIM1, LL_HRTIM_TIMER_F, LL_HRTIM_BURSTMODE_MAINTAINCLOCK);
  LL_HRTIM_ForceUpdate(HRTIM1, LL_HRTIM_TIMER_F);
  LL_HRTIM_TIM_DisableResyncUpdate(HRTIM1, LL_HRTIM_TIMER_F);
  LL_HRTIM_OUT_SetPolarity(HRTIM1, LL_HRTIM_OUTPUT_TF1, LL_HRTIM_OUT_POSITIVE_POLARITY);
  LL_HRTIM_OUT_SetOutputSetSrc(HRTIM1, LL_HRTIM_OUTPUT_TF1, LL_HRTIM_OUTPUTSET_NONE);
  LL_HRTIM_OUT_SetOutputResetSrc(HRTIM1, LL_HRTIM_OUTPUT_TF1, LL_HRTIM_OUTPUTRESET_NONE);
  LL_HRTIM_OUT_SetIdleMode(HRTIM1, LL_HRTIM_OUTPUT_TF1, LL_HRTIM_OUT_NO_IDLE);
  LL_HRTIM_OUT_SetIdleLevel(HRTIM1, LL_HRTIM_OUTPUT_TF1, LL_HRTIM_OUT_IDLELEVEL_INACTIVE);
  LL_HRTIM_OUT_SetFaultState(HRTIM1, LL_HRTIM_OUTPUT_TF1, LL_HRTIM_OUT_FAULTSTATE_NO_ACTION);
  LL_HRTIM_OUT_SetChopperMode(HRTIM1, LL_HRTIM_OUTPUT_TF1, LL_HRTIM_OUT_CHOPPERMODE_DISABLED);
  LL_HRTIM_OUT_SetPolarity(HRTIM1, LL_HRTIM_OUTPUT_TF2, LL_HRTIM_OUT_POSITIVE_POLARITY);
  LL_HRTIM_OUT_SetOutputSetSrc(HRTIM1, LL_HRTIM_OUTPUT_TF2, LL_HRTIM_OUTPUTSET_NONE);
  LL_HRTIM_OUT_SetOutputResetSrc(HRTIM1, LL_HRTIM_OUTPUT_TF2, LL_HRTIM_OUTPUTRESET_NONE);
  LL_HRTIM_OUT_SetIdleMode(HRTIM1, LL_HRTIM_OUTPUT_TF2, LL_HRTIM_OUT_NO_IDLE);
  LL_HRTIM_OUT_SetIdleLevel(HRTIM1, LL_HRTIM_OUTPUT_TF2, LL_HRTIM_OUT_IDLELEVEL_INACTIVE);
  LL_HRTIM_OUT_SetFaultState(HRTIM1, LL_HRTIM_OUTPUT_TF2, LL_HRTIM_OUT_FAULTSTATE_NO_ACTION);
  LL_HRTIM_OUT_SetChopperMode(HRTIM1, LL_HRTIM_OUTPUT_TF2, LL_HRTIM_OUT_CHOPPERMODE_DISABLED);
  /* USER CODE BEGIN HRTIM1_Init 2 */

  /* USER CODE END HRTIM1_Init 2 */
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOC);
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);
  /**HRTIM1 GPIO Configuration
  PB12   ------> HRTIM1_CHC1
  PB13   ------> HRTIM1_CHC2
  PB14   ------> HRTIM1_CHD1
  PB15   ------> HRTIM1_CHD2
  PC6   ------> HRTIM1_CHF1
  PC7   ------> HRTIM1_CHF2
  PC8   ------> HRTIM1_CHE1
  PA8   ------> HRTIM1_CHA1
  */
  GPIO_InitStruct.Pin = BUCKBOOST_P1_DRIVE_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_13;
  LL_GPIO_Init(BUCKBOOST_P1_DRIVE_GPIO_Port, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = BUCKBOOST_N1_DRIVE_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_13;
  LL_GPIO_Init(BUCKBOOST_N1_DRIVE_GPIO_Port, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = BUCKBOOST_N2_DRIVE_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_13;
  LL_GPIO_Init(BUCKBOOST_N2_DRIVE_GPIO_Port, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = BUCKBOOST_P2_DRIVE_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_13;
  LL_GPIO_Init(BUCKBOOST_P2_DRIVE_GPIO_Port, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = BUCK_RED_DRIVE_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_13;
  LL_GPIO_Init(BUCK_RED_DRIVE_GPIO_Port, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = RC_TP4_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_13;
  LL_GPIO_Init(RC_TP4_GPIO_Port, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = BUCK_GREEN_DRIVE_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_3;
  LL_GPIO_Init(BUCK_GREEN_DRIVE_GPIO_Port, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = BUCK_BLUE_DRIVE_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_13;
  LL_GPIO_Init(BUCK_BLUE_DRIVE_GPIO_Port, &GPIO_InitStruct);

}

/**
  * @brief UCPD1 Initialization Function
  * @param None
  * @retval None
  */
void MX_UCPD1_Init(void)
{

  /* USER CODE BEGIN UCPD1_Init 0 */

  /* USER CODE END UCPD1_Init 0 */

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* Peripheral clock enable */
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_UCPD1);

  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);
  /**UCPD1 GPIO Configuration
  PB4   ------> UCPD1_CC2
  PB6   ------> UCPD1_CC1
  */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_4;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = LL_GPIO_PIN_6;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN UCPD1_Init 1 */

  /* USER CODE END UCPD1_Init 1 */
  /* USER CODE BEGIN UCPD1_Init 2 */

  /* USER CODE END UCPD1_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  LL_USART_InitTypeDef USART_InitStruct = {0};

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  LL_RCC_SetUSARTClockSource(LL_RCC_USART3_CLKSOURCE_PCLK1);

  /* Peripheral clock enable */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART3);

  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOC);
  /**USART3 GPIO Configuration
  PC10   ------> USART3_TX
  PC11   ------> USART3_RX
  */
  GPIO_InitStruct.Pin = USART3_TX_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_7;
  LL_GPIO_Init(USART3_TX_GPIO_Port, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = USART3_RX_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_7;
  LL_GPIO_Init(USART3_RX_GPIO_Port, &GPIO_InitStruct);

  /* USART3 DMA Init */

  /* USART3_RX Init */
  LL_DMA_SetPeriphRequest(DMA1, LL_DMA_CHANNEL_1, LL_DMAMUX_REQ_USART3_RX);

  LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_CHANNEL_1, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);

  LL_DMA_SetChannelPriorityLevel(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PRIORITY_LOW);

  LL_DMA_SetMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MODE_NORMAL);

  LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PERIPH_NOINCREMENT);

  LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MEMORY_INCREMENT);

  LL_DMA_SetPeriphSize(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PDATAALIGN_BYTE);

  LL_DMA_SetMemorySize(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MDATAALIGN_BYTE);

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  USART_InitStruct.PrescalerValue = LL_USART_PRESCALER_DIV4;
  USART_InitStruct.BaudRate = 115200;
  USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
  USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
  USART_InitStruct.Parity = LL_USART_PARITY_NONE;
  USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
  USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
  USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
  LL_USART_Init(USART3, &USART_InitStruct);
  LL_USART_SetTXFIFOThreshold(USART3, LL_USART_FIFOTHRESHOLD_1_8);
  LL_USART_SetRXFIFOThreshold(USART3, LL_USART_FIFOTHRESHOLD_1_8);
  LL_USART_DisableFIFO(USART3);
  LL_USART_ConfigAsyncMode(USART3);

  /* USER CODE BEGIN WKUPType USART3 */

  /* USER CODE END WKUPType USART3 */

  LL_USART_Enable(USART3);

  /* Polling USART3 initialisation */
  while((!(LL_USART_IsActiveFlag_TEACK(USART3))) || (!(LL_USART_IsActiveFlag_REACK(USART3))))
  {
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * Enable DMA controller clock
  */
void MX_DMA_Init(void)
{

  /* Init with LL driver */
  /* DMA controller clock enable */
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMAMUX1);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);

  /* DMA interrupt init */
  /* DMA1_Channel1_IRQn interrupt configuration */
  NVIC_SetPriority(DMA1_Channel1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
  NVIC_EnableIRQ(DMA1_Channel1_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
void MX_GPIO_Init(void)
{
  LL_EXTI_InitTypeDef EXTI_InitStruct = {0};
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOC);
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOD);

  /**/
  LL_GPIO_ResetOutputPin(BUCKBOOST_LOAD_1_GPIO_Port, BUCKBOOST_LOAD_1_Pin);

  /**/
  LL_GPIO_ResetOutputPin(BUCKBOOST_LOAD_2_GPIO_Port, BUCKBOOST_LOAD_2_Pin);

  /**/
  LL_GPIO_ResetOutputPin(BUCKBOOST_USBPD_EN_GPIO_Port, BUCKBOOST_USBPD_EN_Pin);

  /**/
  LL_GPIO_ResetOutputPin(LD3_GPIO_Port, LD3_Pin);

  /**/
  LL_GPIO_ResetOutputPin(LD2_GPIO_Port, LD2_Pin);

  /**/
  LL_GPIO_ResetOutputPin(USBPD_1A_PROTECT_GPIO_Port, USBPD_1A_PROTECT_Pin);

  /**/
  LL_GPIO_ResetOutputPin(USBPD_550mA_PROTECT_GPIO_Port, USBPD_550mA_PROTECT_Pin);

  /**/
  LL_GPIO_ResetOutputPin(LD5_GPIO_Port, LD5_Pin);

  /**/
  LL_GPIO_ResetOutputPin(LD4_GPIO_Port, LD4_Pin);

  /**/
  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTC, LL_SYSCFG_EXTI_LINE13);

  /**/
  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTC, LL_SYSCFG_EXTI_LINE4);

  /**/
  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTC, LL_SYSCFG_EXTI_LINE5);

  /**/
  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTB, LL_SYSCFG_EXTI_LINE2);

  /**/
  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTB, LL_SYSCFG_EXTI_LINE10);

  /**/
  EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_13;
  EXTI_InitStruct.LineCommand = ENABLE;
  EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
  EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING;
  LL_EXTI_Init(&EXTI_InitStruct);

  /**/
  EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_4;
  EXTI_InitStruct.LineCommand = ENABLE;
  EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
  EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING;
  LL_EXTI_Init(&EXTI_InitStruct);

  /**/
  EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_5;
  EXTI_InitStruct.LineCommand = ENABLE;
  EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
  EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING;
  LL_EXTI_Init(&EXTI_InitStruct);

  /**/
  EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_2;
  EXTI_InitStruct.LineCommand = ENABLE;
  EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
  EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING;
  LL_EXTI_Init(&EXTI_InitStruct);

  /**/
  EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_10;
  EXTI_InitStruct.LineCommand = ENABLE;
  EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
  EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING;
  LL_EXTI_Init(&EXTI_InitStruct);

  /**/
  LL_GPIO_SetPinPull(JOYSTICK_SEL_GPIO_Port, JOYSTICK_SEL_Pin, LL_GPIO_PULL_UP);

  /**/
  LL_GPIO_SetPinPull(JOYSTICK_LEFT_GPIO_Port, JOYSTICK_LEFT_Pin, LL_GPIO_PULL_UP);

  /**/
  LL_GPIO_SetPinPull(JOYSTICK_DOWN_GPIO_Port, JOYSTICK_DOWN_Pin, LL_GPIO_PULL_UP);

  /**/
  LL_GPIO_SetPinPull(JOYSTICK_RIGHT_GPIO_Port, JOYSTICK_RIGHT_Pin, LL_GPIO_PULL_UP);

  /**/
  LL_GPIO_SetPinPull(JOYSTICK_UP_GPIO_Port, JOYSTICK_UP_Pin, LL_GPIO_PULL_UP);

  /**/
  LL_GPIO_SetPinMode(JOYSTICK_SEL_GPIO_Port, JOYSTICK_SEL_Pin, LL_GPIO_MODE_INPUT);

  /**/
  LL_GPIO_SetPinMode(JOYSTICK_LEFT_GPIO_Port, JOYSTICK_LEFT_Pin, LL_GPIO_MODE_INPUT);

  /**/
  LL_GPIO_SetPinMode(JOYSTICK_DOWN_GPIO_Port, JOYSTICK_DOWN_Pin, LL_GPIO_MODE_INPUT);

  /**/
  LL_GPIO_SetPinMode(JOYSTICK_RIGHT_GPIO_Port, JOYSTICK_RIGHT_Pin, LL_GPIO_MODE_INPUT);

  /**/
  LL_GPIO_SetPinMode(JOYSTICK_UP_GPIO_Port, JOYSTICK_UP_Pin, LL_GPIO_MODE_INPUT);

  /**/
  GPIO_InitStruct.Pin = BUCKBOOST_LOAD_1_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(BUCKBOOST_LOAD_1_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = BUCKBOOST_LOAD_2_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(BUCKBOOST_LOAD_2_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = BUCKBOOST_USBPD_EN_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(BUCKBOOST_USBPD_EN_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = LD3_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(LD3_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = USBPD_1A_PROTECT_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(USBPD_1A_PROTECT_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = USBPD_550mA_PROTECT_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(USBPD_550mA_PROTECT_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = LD5_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(LD5_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = LD4_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(LD4_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  NVIC_SetPriority(EXTI2_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
  NVIC_EnableIRQ(EXTI2_IRQn);
  NVIC_SetPriority(EXTI4_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
  NVIC_EnableIRQ(EXTI4_IRQn);
  NVIC_SetPriority(EXTI9_5_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
  NVIC_EnableIRQ(EXTI9_5_IRQn);
  NVIC_SetPriority(EXTI15_10_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
  NVIC_EnableIRQ(EXTI15_10_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM2 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM2) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

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

#ifdef  USE_FULL_ASSERT
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

/*SimulinkGeneratedCode*/
