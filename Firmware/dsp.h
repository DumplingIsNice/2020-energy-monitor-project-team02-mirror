/* Remove the gain and shifts added by all the analogue circuitry to get
 * back the original sensor voltage value
 */
float reverse_gain(float adc_voltage);
