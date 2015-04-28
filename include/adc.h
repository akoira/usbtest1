/*
 * adc.h
 *
 *  Created on: Apr 9, 2015
 *      Author: akoiro
 */

#ifndef ADC_H_
#define ADC_H_

#include "stm32f4xx_hal.h"
#include "stm32f4_discovery.h"
#include "common.h"

void ADC_INIT(ADC_HandleTypeDef* handleTypeDef, uint32_t* uhADCxConvertedValue);
void __ADC_INIT(ADC_HandleTypeDef* hadc);
void __ADC_DEINIT(ADC_HandleTypeDef *hadc);

#endif /* ADC1_H_ */
