/* Remove the gain and shifts added by all the analogue circuitry to get
 * back the original sensor voltage value
 */
float reverseVoltageGain(float adc_voltage);
float reverseCurrentGain(float adc_voltage);
