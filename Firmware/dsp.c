#include "common.h"
#include "adc.h"
#include "timer0.h"

#include <avr/interrupt.h>
#include <stdbool.h>

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

/* Zero Crossing Interrupt */
/* Currently sampling one cycle of the waveform at a time */

static volatile bool signal_start = false;

/* Initializes voltage zero crossing interrupt */
void voltage_zc_interrupt_init()
{	
	SET_PORT(EIMSK, INT0);
	
	/* Rising edge trigger */
	SET_PORT(EICRA, ISC01), SET_PORT(EICRA, ISC00);
	
	/* Changing Edge trigger 
	EICRA |= (1 << ISC00); 
	EICRA &= ~(1 << ISC01); */
}

bool is_sampling()
{
	return signal_start;
}

void check_cycle_complete()
{
	static int cycles = 0;
	
	if (cycles >= CYCLE_SAMPLED - 1){
		signal_start = false;
		cycles = 0;
	} else if (cycles < CYCLE_SAMPLED - 1){
		signal_start = true;
		cycles++;
	}
}

ISR(INT0_vect)
{
	//Use this LED to check if interrupt is called.

	
	/* Zero crossing indicates the start to a new cycle of sampling */
	//signal_start = !signal_start; 
	
	check_cycle_complete();
	
	if(signal_start){
		timer0_start();
	} else if (!signal_start){
		timer0_stop();
		TGL_PORT(PORTB, PORTB5);
	}
}