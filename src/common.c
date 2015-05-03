/*
 * common.c
 *
 *  Created on: 28 апр. 2015 г.
 *      Author: andrey
 */

#include "common.h"

unsigned int N = 10;
/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
unsigned int Filter(unsigned int sample, unsigned int *sum){
    *sum -= *sum/N;
    *sum += sample;

    return *sum/N;
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
  /* Turn LED4 (RED) on */
  BSP_LED_On(LED4);
  while(1)
  {
  }
}

