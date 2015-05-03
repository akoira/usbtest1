/*
 * adc.c
 *
 *  Created on: Apr 8, 2015
 *      Author: akoiro
 */
#include "adc.h"

void ADC_INIT(ADC_HandleTypeDef* handleTypeDef,
		uint32_t *uhADCxConvertedValue)
{
	 /*##-1- Configure the ADC peripheral #######################################*/
	  handleTypeDef->Instance = ADC1;

	  handleTypeDef->Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV2;
	  handleTypeDef->Init.Resolution = ADC_RESOLUTION_12B;
	  handleTypeDef->Init.ScanConvMode = ENABLE;
	  handleTypeDef->Init.ContinuousConvMode = ENABLE;
	  handleTypeDef->Init.DiscontinuousConvMode = DISABLE;
	  handleTypeDef->Init.NbrOfDiscConversion = 0;
	  handleTypeDef->Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	  handleTypeDef->Init.ExternalTrigConv = ADC_EXTERNALTRIGCONV_T1_CC1;
	  handleTypeDef->Init.DataAlign = ADC_DATAALIGN_RIGHT;
	  handleTypeDef->Init.NbrOfConversion = 3;
	  handleTypeDef->Init.DMAContinuousRequests = ENABLE;
	  handleTypeDef->Init.EOCSelection = DISABLE;
	  if(HAL_ADC_Init(handleTypeDef) != HAL_OK)
	  {
	    /* Initialization Error */
	    Error_Handler();
	  }

	  /*##-2- Configure ADC regular channel ######################################*/
	  /* Note: Considering IT occurring after each number of size of              */
	  /*       "uhADCxConvertedValue"  ADC conversions (IT by DMA end             */
	  /*       of transfer), select sampling time and ADC clock with sufficient   */
	  /*       duration to not create an overhead situation in IRQHandler.        */

	  ADC_ChannelConfTypeDef sConfig;
	  sConfig.Channel = ADC_CHANNEL_10;
	  sConfig.Rank = 1;
	  sConfig.SamplingTime = ADC_SAMPLETIME_28CYCLES;
	  sConfig.Offset = 0;

	  if(HAL_ADC_ConfigChannel(handleTypeDef, &sConfig) != HAL_OK)
	  {
	    /* Channel Configuration Error */
	    Error_Handler();
	  }

	  ADC_ChannelConfTypeDef sConfig1;
	  sConfig1.Channel = ADC_CHANNEL_11;
	  sConfig1.Rank = 2;
	  sConfig1.SamplingTime = ADC_SAMPLETIME_28CYCLES;
	  sConfig1.Offset = 0;

	  if(HAL_ADC_ConfigChannel(handleTypeDef, &sConfig1) != HAL_OK)
	  {
	    /* Channel Configuration Error */
	    Error_Handler();
	  }

	  ADC_ChannelConfTypeDef sConfig2;
	  sConfig2.Channel = ADC_CHANNEL_12;
	  sConfig2.Rank = 3;
	  sConfig2.SamplingTime = ADC_SAMPLETIME_28CYCLES;
	  sConfig2.Offset = 0;

	  if(HAL_ADC_ConfigChannel(handleTypeDef, &sConfig2) != HAL_OK)
	  {
	    /* Channel Configuration Error */
	    Error_Handler();
	  }

	  /*##-3- Start the conversion process and enable interrupt ##################*/
	  if(HAL_ADC_Start_DMA(handleTypeDef, uhADCxConvertedValue, 3) != HAL_OK)
	  {
	    /* Start Conversation Error */
	    Error_Handler();
	  }
}

void __ADC_INIT(ADC_HandleTypeDef* hadc)
{

	  __GPIOC_CLK_ENABLE();
	  __DMA2_CLK_ENABLE();
	  __ADC1_CLK_ENABLE();

  GPIO_InitTypeDef          GPIO_InitStruct;
  GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);



  static DMA_HandleTypeDef  hdma_adc;
  hdma_adc.Instance = DMA2_Stream0;

  hdma_adc.Init.Channel  = DMA_CHANNEL_0;
  hdma_adc.Init.Direction = DMA_PERIPH_TO_MEMORY;
  hdma_adc.Init.PeriphInc = DMA_PINC_DISABLE;
  hdma_adc.Init.MemInc = DMA_MINC_ENABLE;
  hdma_adc.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
  hdma_adc.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
  hdma_adc.Init.Mode = DMA_CIRCULAR;
  hdma_adc.Init.Priority = DMA_PRIORITY_HIGH;
  hdma_adc.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
  hdma_adc.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_HALFFULL;
  hdma_adc.Init.MemBurst = DMA_MBURST_SINGLE;
  hdma_adc.Init.PeriphBurst = DMA_PBURST_SINGLE;

  HAL_DMA_Init(&hdma_adc);

  /* Associate the initialized DMA handle to the the ADC handle */
  __HAL_LINKDMA(hadc, DMA_Handle, hdma_adc);

  /*##-4- Configure the NVIC for DMA #########################################*/
  /* NVIC configuration for DMA transfer complete interrupt */
  HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);
}


void __ADC_DEINIT(ADC_HandleTypeDef *hadc){
	  static DMA_HandleTypeDef  hdma_adc;

	  HAL_GPIO_DeInit(GPIOC, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2);

	  HAL_DMA_DeInit(&hdma_adc);

	  HAL_NVIC_DisableIRQ(DMA2_Stream0_IRQn);
}



