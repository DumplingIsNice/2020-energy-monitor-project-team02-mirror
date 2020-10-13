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
/* Assuming we create one new point per sample point, we get (3n - 4) new points */
#define INTERPOLATED_ARRAY_SIZE (3 * RAW_ARRAY_SIZE - 4)

/* Raw Voltage and Current Readings (Along with time value of each reading) */
/* The extern forward decleration in the same file as the variable definition
 * confuses the Proteus simulator - so wrap it in the #ifndef to ensure
 * we do not have the extern declerations in the same file the variables are
 * defined in ("dsp.c")
 * */
#ifndef DSP_C
extern volatile int complete_sampling;

extern volatile unsigned adc_voltages[RAW_ARRAY_SIZE];
extern volatile unsigned adc_voltages_t[RAW_ARRAY_SIZE];
extern volatile unsigned adc_voltages_head;

extern volatile unsigned adc_currents[RAW_ARRAY_SIZE];
extern volatile unsigned adc_currents_t[RAW_ARRAY_SIZE];
extern volatile unsigned adc_currents_head;

/* Reverse Gained array of values */
extern volatile float raw_voltages[RAW_ARRAY_SIZE];
extern volatile float raw_voltages_t[RAW_ARRAY_SIZE];

extern volatile float raw_currents[RAW_ARRAY_SIZE];
extern volatile float raw_currents_t[RAW_ARRAY_SIZE];
#endif /* DSP_C */

void reverse_voltage_gain();
void reverse_current_gain();

void adc2real_voltage();
void adc2real_current();
void cubic_interpolate();

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
