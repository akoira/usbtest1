/*
 * adc2.c
 *
 *  Created on: Apr 8, 2015
 *      Author: akoiro
 */
#include "adc2.h"

void ADC2_INIT(ADC_HandleTypeDef* hadc)
{
  GPIO_InitTypeDef          GPIO_InitStruct;
  static DMA_HandleTypeDef  hdma_adc2;

  __HAL_RCC_ADC2_CLK_ENABLE();

  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  hdma_adc2.Instance = DMA2_Stream1;

  hdma_adc2.Init.Channel  = DMA_CHANNEL_1;
  hdma_adc2.Init.Direction = DMA_PERIPH_TO_MEMORY;
  hdma_adc2.Init.PeriphInc = DMA_PINC_DISABLE;
  hdma_adc2.Init.MemInc = DMA_MINC_ENABLE;
  hdma_adc2.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
  hdma_adc2.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
  hdma_adc2.Init.Mode = DMA_CIRCULAR;
  hdma_adc2.Init.Priority = DMA_PRIORITY_HIGH;
  hdma_adc2.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
  hdma_adc2.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_HALFFULL;
  hdma_adc2.Init.MemBurst = DMA_MBURST_SINGLE;
  hdma_adc2.Init.PeriphBurst = DMA_PBURST_SINGLE;

  HAL_DMA_Init(&hdma_adc2);

  /* Associate the initialized DMA handle to the the ADC handle */
  __HAL_LINKDMA(hadc, DMA_Handle, hdma_adc2);

  /*##-4- Configure the NVIC for DMA #########################################*/
  /* NVIC configuration for DMA transfer complete interrupt */
  HAL_NVIC_SetPriority(DMA2_Stream1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream1_IRQn);
}


void ADC2_DEINIT(ADC_HandleTypeDef *hadc){
	  static DMA_HandleTypeDef  hdma_adc1;

	  HAL_GPIO_DeInit(GPIOB, GPIO_PIN_1);

	  HAL_DMA_DeInit(&hdma_adc1);

	  HAL_NVIC_DisableIRQ(DMA2_Stream1_IRQn);
}




