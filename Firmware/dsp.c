#include "common.h"
#include "dsp.h"
#include "adc.h"
#include "timer0.h"

#include <avr/interrupt.h>
#include <stdbool.h>

extern volatile uint16_t miliseconds;

/* Inital channel is voltage (we sample voltage first, then current) */
int current_adc_channel = ADC_CH_VOLTAGE;

/* Raw Voltage and Current Readings (Along with time value of each reading) */
float volatile adc_voltages[RAW_ARRAY_SIZE];
float volatile adc_voltages_t[RAW_ARRAY_SIZE];
unsigned volatile adc_voltages_head; /* index to next free space in array */

float volatile adc_currents[RAW_ARRAY_SIZE];
float volatile adc_currents_t[RAW_ARRAY_SIZE];
unsigned volatile adc_currents_head;  /* index to next free space in array */

/* Reverse Gained array of values */
float volatile raw_voltages[RAW_ARRAY_SIZE];
float volatile raw_voltages_t[RAW_ARRAY_SIZE];

float volatile raw_currents[RAW_ARRAY_SIZE];
float volatile raw_currents_t[RAW_ARRAY_SIZE];

/* Remove the gain and shifts added by all the analogue circuitry to get
 * back the original sensor voltage value
 */
void reverse_voltage_gain()
{
	int i;
	float vOffset = 2.1;
	
	// Voltage divider inverse gain
	uint16_t Rb1 = 3300;
	uint16_t Ra1 = 56000;
	float dividerGain = 1/(float)(Rb1/(float)(Ra1 + Rb1));
	
	
	// Voltage amplifier gain
	uint16_t R2 = 4700;
	uint16_t R1 = 1500;
	float amplifierGain =  1/(float)(R2/((float)R1));
	
	
	//float reversedVoltage = (dividerGain * amplifierGain * adc_voltage) - vOffset;
	for (i = 0; i < RAW_ARRAY_SIZE; ++i) {
		raw_voltages[i] = (adc_voltages[i] - vOffset) * dividerGain * amplifierGain;
		raw_voltages_t[i] = adc_voltages_t[i];
	}
}

/* Remove the gain and shifts added by all the analogue circuitry to get
 * back the original sensor current value
 */
void reverse_current_gain()
{
	int i;
	float acVoltage;
	float vOffset = 2.1;
	
	
	// Voltage divider inverse gain
	float Rs1 = 0.56;
	float dividerGain = 1/(float)(Rs1);
	
	
	// Voltage amplifier gain
	uint16_t R2 = 56000;
	uint16_t R1 = 22000;
	float amplifierGain =  1/(float)(R2/((float)R1));
	
	
	//float reversedCurrent = (dividerGain * amplifierGain * adc_current) - vOffset;
	for (i = 0; i < RAW_ARRAY_SIZE; ++i) {
		raw_currents[i] = (adc_currents[i] - vOffset) * dividerGain * amplifierGain;
		raw_currents_t[i] = adc_currents_t[i];
	}
}

/* Zero Crossing Interrupt */
/* Currently sampling one cycle of the waveform at a time */

bool signal_start = false;
static volatile int16_t elapsed_cycle_time = 0;

ISR(INT0_vect)
{
	//Use this LED to check if interrupt is called.
	//TGL_PORT(PORTB, PORTB5);
	
	/* Zero crossing indicates the start to a new cycle of sampling */
	signal_start = !signal_start;
}

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

void set_elapsed_cycle()
{
	elapsed_cycle_time = miliseconds;
}

/* Returns the calculated period of current sample */
int16_t get_period()
{
	int16_t period = 0;
	
	period = elapsed_cycle_time/CYCLE_SAMPLED;

	return period;
}

/* Checks if the required cycles have elapsed */
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