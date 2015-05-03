/*
 * adc2.h
 *
 *  Created on: Apr 9, 2015
 *      Author: akoiro
 */

#ifndef ADC2_H_
#define ADC2_H_

#include "stm32f4xx_hal.h"
#include "stm32f4_discovery.h"

void ADC2_INIT(ADC_HandleTypeDef* hadc);
void ADC2_DEINIT(ADC_HandleTypeDef *hadc);
#endif /* ADC2_H_ */
