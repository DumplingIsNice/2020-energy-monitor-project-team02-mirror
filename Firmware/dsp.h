/* Remove the gain and shifts added by all the analogue circuitry to get
 * back the original sensor voltage value
 */

#ifndef DSP_H_
#define DSP_H_

#include <stdbool.h>

float reverse_voltage_gain(float adc_voltage);
float reverse_current_gain(float adc_voltage);

/* Returns whether is sampling or not */
bool is_sampling();

/* Initializes voltage zero crossing interrupt */
void voltage_zc_interrupt_init();

/* Initializes current zero crossing interrupt (Not implemented) */
// void current_zc_interrupt_init();

#endif 