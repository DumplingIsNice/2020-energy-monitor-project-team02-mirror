/*
* dsp.h
*
* Created: 11/09/2020
* Author: Ankush Patel, Rukin Swedlund
*
* Functions regarding signal processing and calculations
*/

#ifndef DSP_H_
#define DSP_H_

#include <stdbool.h>

/* [Global] Arrays to hold values (defined in dsp.c) */

#define ADC_CH_VOLTAGE 0
#define ADC_CH_CURRENT 1

extern int current_adc_channel;

#define CYCLE_SAMPLED 1
#define RAW_ARRAY_SIZE (20 * CYCLE_SAMPLED)
/* Assuming we create one new point per sample point, we get (2n - 2) new points */
#define INTERPOLATED_ARRAY_SIZE (2 * RAW_ARRAY_SIZE - 1)

/* Raw Voltage and Current Readings (Along with time value of each reading) */
/* The extern forward decleration in the same file as the variable definition
 * confuses the Proteus simulator - so wrap it in the #ifndef to ensure
 * we do not have the extern declerations in the same file the variables are
 * defined in ("dsp.c")
 * */
#ifndef DSP_C
extern volatile unsigned currently_sampling;

extern volatile unsigned adc_voltages[RAW_ARRAY_SIZE];
extern volatile unsigned adc_voltages_head;

extern volatile unsigned adc_currents[RAW_ARRAY_SIZE];
extern volatile unsigned adc_currents_head;

/* Reverse Gained array of values */
extern float raw_voltages[RAW_ARRAY_SIZE];
extern float raw_currents[RAW_ARRAY_SIZE];

extern float interpolated_voltages[INTERPOLATED_ARRAY_SIZE];
extern float interpolated_currents[INTERPOLATED_ARRAY_SIZE];

extern float power;
extern float rms_voltage;
extern float pk_current;
extern float energy;
#endif /* DSP_C */

void adc2real_voltage();
void adc2real_current();
void cubic_interpolate();
void calculate_power();
void calculate_energy();
void calculate_rms_voltage();
void calculate_pk_current();

/* Returns the calculated period of current sample */
uint16_t get_period();

/* Initializes voltage zero crossing interrupt */
void voltage_zc_interrupt_init();

#endif 
