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

extern volatile int complete_sampling;

// Functions

/* MISC */
void adc_init();
uint16_t adc_read();
float adc_convert(uint16_t value);

/* Functions for turning adc on and off*/
void adc_on();
void adc_off();

void sampling_init();

#endif
