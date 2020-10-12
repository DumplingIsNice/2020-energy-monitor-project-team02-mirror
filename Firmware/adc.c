#include "common.h"
#include "timer0.h"
#include "adc.h"
#include "dsp.h"

#include <avr/interrupt.h>
#include <string.h>

#define MILISECOND_DELAY 1+0.5 /* Delay from Vzc and setup for sampling */

extern volatile uint16_t miliseconds;  /* defined in timer0.c */
extern bool signal_start; /* defined in dsp.c */

bool print_complete = false;

static bool complete_sampling = false;

void adc_set_channel(uint8_t channel)
{
	ADMUX &= ~((1 << MUX2) | (1 << MUX1) | (1 << MUX0));
	ADMUX |= channel;

	current_adc_channel = channel;
}

/* This function reads the current ADC channel and return results */
uint16_t adc_read()
{
	ADCSRA |= (1 << ADSC); // Start ADC conversion

	//ADIF bit is checked to see if it is 0
	//If ADIF bit is not 0, wait until it becomes 0
	while ((ADCSRA & (1 << ADIF)) == 0) { ;
	}

	return ADC;
}

// Convert a single adcCount input and return voltage
float adc_convert(uint16_t adcCount)
{
	float instantVoltage = (5 * adcCount) / (float) 1024;
	return instantVoltage;
}

/* ADC initialisation
 * Default channel is channel zero
 */
void adc_init()
{
	/* Enable ADC, Start ADC Conversion, Enable ADC AutoTrigger, Enable ADC interrupt on conversion complete
	 * To get the full 10-bit resolution , the ADC clock must be at a maximum of 200 KHz
	 * Prescaler = f_cpu / 200000
	 */
	SET_PORT(ADCSRA, ADEN), SET_PORT(ADCSRA, ADSC), SET_PORT(ADCSRA, ADATE), SET_PORT(ADCSRA, ADIE);
#ifdef HARDWARE_BUILD
	/* For hardware, prescaler must be 128 */
	SET_PORT(ADCSRA, ADPS2), SET_PORT(ADCSRA, ADPS1), SET_PORT(ADCSRA, ADPS0);
#else
	/* For simulation, prescaler can be 4 */
	SET_PORT(ADCSRA, ADPS1);
#endif /* HARDWARE_BUILD */

	/* Select Timer0 CTC A as ADC conversion trigger */
	SET_PORT(ADCSRB, ADTS1), SET_PORT(ADCSRB, ADTS0);
}

/* Assuming we sample voltage first */

ISR(ADC_vect)
{
	/* Occurs every 1 ms (uncomment LED toggle code below to test) */
		/* PORTB ^= 1 << PB5; */
		
	/* Hold array values so it's not overwritten during calculation AND debug printing */
	if(print_complete){
		signal_start = false; /* We must skip the current cycle as memcpy takes time */
		print_complete = false; /* Replace with process_complete for ISR calc */
		
		memcpy(&raw_voltages, &adc_voltages, sizeof adc_voltages);
		//memcpy(&raw_currents, &adc_currents, sizeof adc_currents);
	}
		
	if (signal_start){
		/* Perform non-time critical operations first */
		set_elapsed_cycle();
		signal_start = false;
		complete_sampling = false;
		adc_voltages_head = 0;
		adc_currents_head = 0;
		/* Time critical operations */
		adc_set_channel(ADC_CH_VOLTAGE); /* Implicitly assumes voltage is first sample */
		timer0_reset();
	}

	uint16_t adc_value = ADC;
	
	if(!complete_sampling){
		
		if (current_adc_channel == ADC_CH_VOLTAGE) {
			// raw_voltages[raw_voltages_head] = reverse_voltage_gain(adc_convert(adc_value));
			adc_voltages[adc_voltages_head] = adc_convert(adc_value);
			adc_voltages_t[adc_voltages_head] = miliseconds+MILISECOND_DELAY;
			++adc_voltages_head;

			/* Switch the channel of the next sample */
			adc_set_channel(ADC_CH_CURRENT);
		} else if (current_adc_channel == ADC_CH_CURRENT) {
			// raw_currents[raw_currents_head] = reverse_current_gain(adc_convert(adc_value));
			adc_currents[adc_currents_head] = adc_convert(adc_value);
			adc_currents_t[adc_currents_head] = miliseconds+MILISECOND_DELAY;
			++adc_currents_head;
		
			/* Switch the channel of the next sample */
			adc_set_channel(ADC_CH_VOLTAGE);
		}		
	}
	
	if (adc_voltages_head >= RAW_ARRAY_SIZE) {
		adc_voltages_head = 0;
	}
	if (adc_currents_head >= RAW_ARRAY_SIZE) {
		adc_currents_head = 0;
		complete_sampling = true;
	} 
}

void adc_on()
{
	SET_PORT(ADCSRA, ADEN);
}

void adc_off()
{
	CLR_PORT(ADCSRA, ADEN);
}