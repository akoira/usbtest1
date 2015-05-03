/*
 * adc1.h
 *
 *  Created on: Apr 9, 2015
 *      Author: akoiro
 */

#ifndef ADC1_H_
#define ADC1_H_

#include "stm32f4xx_hal.h"
#include "stm32f4_discovery.h"

void ADC_INIT(ADC_HandleTypeDef* handleTypeDef, ADC_TypeDef* typeDef, uint32_t channel, uint32_t* uhADCxConvertedValue);
void ADC1_INIT(ADC_HandleTypeDef* hadc);
void ADC1_DEINIT(ADC_HandleTypeDef *hadc);

#endif /* ADC1_H_ */
