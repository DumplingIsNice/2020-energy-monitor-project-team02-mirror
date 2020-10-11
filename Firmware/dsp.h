/* Remove the gain and shifts added by all the analogue circuitry to get
 * back the original sensor voltage value
 */

#ifndef DSP_H_
#define DSP_H_

#include <stdbool.h>

/* [Global] Arrays to hold values (defined in dsp.c) */

#define ADC_CH_VOLTAGE 0
#define ADC_CH_CURRENT 1

extern int current_adc_channel;

#define CYCLE_SAMPLED 1
#define RAW_ARRAY_SIZE 10*CYCLE_SAMPLED

extern volatile float raw_voltages[RAW_ARRAY_SIZE];
extern volatile float raw_voltages_t[RAW_ARRAY_SIZE];
extern volatile unsigned raw_voltages_head;

extern volatile float raw_currents[RAW_ARRAY_SIZE];
extern volatile float raw_currents_t[RAW_ARRAY_SIZE];
extern volatile unsigned raw_currents_head;

float reverse_voltage_gain(float adc_voltage);
float reverse_current_gain(float adc_voltage);

/* Record elapsed time at cycle completion */
void set_elapsed_cycle();

/* Returns the calculated period of current sample */
int16_t get_period();

/* Checks if the required cycles have elapsed (For future use) */
void check_cycle_complete();

/* Initializes voltage zero crossing interrupt */
void voltage_zc_interrupt_init();

/* Initializes current zero crossing interrupt (Not implemented) */
// void current_zc_interrupt_init();

#endif 