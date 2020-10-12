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
#define RAW_ARRAY_SIZE (10 * CYCLE_SAMPLED)
#define INTERPOLATED_ARRAY_SIZE (RAW_ARRAY_SIE)

/* Raw Voltage and Current Readings (Along with time value of each reading) */
extern volatile float adc_voltages[RAW_ARRAY_SIZE];
extern volatile float adc_voltages_t[RAW_ARRAY_SIZE];
extern volatile unsigned adc_voltages_head;

extern volatile float adc_currents[RAW_ARRAY_SIZE];
extern volatile float adc_currents_t[RAW_ARRAY_SIZE];
extern volatile unsigned adc_currents_head;

/* Reverse Gained array of values */
extern float volatile raw_voltages[RAW_ARRAY_SIZE];
extern float volatile raw_voltages_t[RAW_ARRAY_SIZE];

extern float volatile raw_currents[RAW_ARRAY_SIZE];
extern float volatile raw_currents_t[RAW_ARRAY_SIZE];

void reverse_voltage_gain();
void reverse_current_gain();

/* Record elapsed time at cycle completion */
void set_elapsed_cycle();

/* Returns the calculated period of current sample */
uint16_t get_period();

/* Checks if the required cycles have elapsed (For future use) */
void check_cycle_complete();

/* Initializes voltage zero crossing interrupt */
void voltage_zc_interrupt_init();

/* Initializes current zero crossing interrupt (Not implemented) */
// void current_zc_interrupt_init();

#endif 
