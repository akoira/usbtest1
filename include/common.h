/*
 * common.h
 *
 *  Created on: 28 апр. 2015 г.
 *      Author: andrey
 */

#ifndef COMMON_H_
#define COMMON_H_

#include "stm32f4_discovery.h"

void Error_Handler(void);
unsigned int Filter(unsigned int sample, unsigned int *sum);

#endif /* COMMON_H_ */
