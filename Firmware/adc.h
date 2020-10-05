/*
* adc.h
*
* Created: 25/09/2020
* Author: Krithik Lekinwala
*
* Functions to do with ADC protocols
*/

#ifndef _ADC_H
#define _ADC_H

#include <stdint.h>

// Functions

/* MISC */
void adc_init();
uint16_t adc_read(uint8_t channel);


/* CONVERSIONS */
float adc_convert(uint16_t value);


#endif
