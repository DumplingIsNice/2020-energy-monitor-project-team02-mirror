#include "common.h"
#include "adc.h"

/* Remove the gain and shifts added by all the analogue circuitry to get
 * back the original sensor voltage value
 */
float reverse_voltage_gain(float adc_voltage)
{
	float vOffset = 2.1;
	
	// Voltage divider inverse gain
	uint16_t Rb1 = 3300;
	uint16_t Ra1 = 56000;
	float dividerGain = 1/(float)(Rb1/(float)(Ra1 + Rb1));
	
	
	// Voltage amplifier gain
	uint16_t R2 = 4700;
	uint16_t R1 = 1500;
	float amplifierGain =  1/(float)(R2/((float)R1));
	
	
	float reversedVoltage = (dividerGain * amplifierGain * adc_voltage) - vOffset;
	
	return reversedVoltage;
}

/* Remove the gain and shifts added by all the analogue circuitry to get
 * back the original sensor current value
 */
float reverse_current_gain(float adc_current)
{
	float acVoltage;
	float vOffset = 2.1;
	
	
	// Voltage divider inverse gain
	float Rs1 = 0.56;
	float dividerGain = 1/(float)(Rs1);
	
	
	// Voltage amplifier gain
	uint16_t R2 = 56000;
	uint16_t R1 = 22000;
	float amplifierGain =  1/(float)(R2/((float)R1));
	
	
	float reversedCurrent = (dividerGain * amplifierGain * adc_current) - vOffset;
	
	return reversedCurrent;
}
