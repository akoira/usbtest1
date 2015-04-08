/*
 * adc1.c
 *
 *  Created on: Apr 8, 2015
 *      Author: akoiro
 */
#include "adc1.h"

void ADC_INIT(ADC_HandleTypeDef* handleTypeDef,
		ADC_TypeDef* typeDef,
		uint32_t channel,
		uint32_t *uhADCxConvertedValue)
{
	  ADC_ChannelConfTypeDef sConfig;
	 /*##-1- Configure the ADC peripheral #######################################*/
	  handleTypeDef->Instance = typeDef;

	  handleTypeDef->Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV2;
	  handleTypeDef->Init.Resolution = ADC_RESOLUTION_12B;
	  handleTypeDef->Init.ScanConvMode = DISABLE;
	  handleTypeDef->Init.ContinuousConvMode = ENABLE;
	  handleTypeDef->Init.DiscontinuousConvMode = DISABLE;
	  handleTypeDef->Init.NbrOfDiscConversion = 0;
	  handleTypeDef->Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	  handleTypeDef->Init.ExternalTrigConv = ADC_EXTERNALTRIGCONV_T1_CC1;
	  handleTypeDef->Init.DataAlign = ADC_DATAALIGN_RIGHT;
	  handleTypeDef->Init.NbrOfConversion = 1;
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
	  sConfig.Channel = channel;
	  sConfig.Rank = 1;
	  sConfig.SamplingTime = ADC_SAMPLETIME_28CYCLES;
	  sConfig.Offset = 0;

	  if(HAL_ADC_ConfigChannel(handleTypeDef, &sConfig) != HAL_OK)
	  {
	    /* Channel Configuration Error */
	    Error_Handler();
	  }

	  /*##-3- Start the conversion process and enable interrupt ##################*/
	  if(HAL_ADC_Start_DMA(handleTypeDef, uhADCxConvertedValue, 1) != HAL_OK)
	  {
	    /* Start Conversation Error */
	    Error_Handler();
	  }
}

void ADC1_INIT(ADC_HandleTypeDef* hadc)
{
  GPIO_InitTypeDef          GPIO_InitStruct;
  static DMA_HandleTypeDef  hdma_adc1;

  __HAL_RCC_ADC1_CLK_ENABLE();

  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);



  hdma_adc1.Instance = DMA2_Stream0;

  hdma_adc1.Init.Channel  = DMA_CHANNEL_0;
  hdma_adc1.Init.Direction = DMA_PERIPH_TO_MEMORY;
  hdma_adc1.Init.PeriphInc = DMA_PINC_DISABLE;
  hdma_adc1.Init.MemInc = DMA_MINC_ENABLE;
  hdma_adc1.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
  hdma_adc1.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
  hdma_adc1.Init.Mode = DMA_CIRCULAR;
  hdma_adc1.Init.Priority = DMA_PRIORITY_HIGH;
  hdma_adc1.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
  hdma_adc1.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_HALFFULL;
  hdma_adc1.Init.MemBurst = DMA_MBURST_SINGLE;
  hdma_adc1.Init.PeriphBurst = DMA_PBURST_SINGLE;

  HAL_DMA_Init(&hdma_adc1);

  /* Associate the initialized DMA handle to the the ADC handle */
  __HAL_LINKDMA(hadc, DMA_Handle, hdma_adc1);

  /*##-4- Configure the NVIC for DMA #########################################*/
  /* NVIC configuration for DMA transfer complete interrupt */
  HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);
}


void ADC1_DEINIT(ADC_HandleTypeDef *hadc){
	  static DMA_HandleTypeDef  hdma_adc1;

	  HAL_GPIO_DeInit(GPIOB, GPIO_PIN_0);

	  HAL_DMA_DeInit(&hdma_adc1);

	  HAL_NVIC_DisableIRQ(DMA2_Stream0_IRQn);
}

void Error_Handler(void)
{
  /* Turn LED4 (RED) on */
  BSP_LED_On(LED4);
  while(1)
  {
  }
}



