/*
* adc.h
*
* Created: 25/09/2020
* Author: Krithik Lekinwala
*
* Functions regarding ADC peripherals and protocols
*/

#ifndef _ADC_H
#define _ADC_H

#include <stdint.h>

void adc_init();
void adc_set_channel(uint8_t channel);

#endif
