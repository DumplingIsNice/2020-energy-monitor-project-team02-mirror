#include "common.h"
#include "timer0.h"
#include "adc.h"
#include "dsp.h"

#include <avr/interrupt.h>

#define MILISECOND_DELAY 1+0.5 /* Delay from Vzc and setup for sampling */

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
	return (5 * adcCount) / (float) 1024;
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

ISR(ADC_vect)
{
	/* Occurs every 1 ms (uncomment LED toggle code below to test) */
	/*TGL_PORT(PORTB, PORTB5);*/

	if (current_adc_channel == ADC_CH_VOLTAGE) {
		adc_voltages[adc_voltages_head] = ADC;
		adc_voltages_t[adc_voltages_head] = miliseconds;
		++adc_voltages_head;

		/* Switch the channel of the next sample */
		adc_set_channel(ADC_CH_CURRENT);
	} else {
		adc_currents[adc_currents_head] = ADC;
		adc_currents_t[adc_currents_head] = miliseconds;
		++adc_currents_head;

		/* Switch the channel of the next sample */
		adc_set_channel(ADC_CH_VOLTAGE);
	}

	miliseconds++;
}

/* Assuming we sample voltage first */

#if 0

ISR(ADC_vect)
{
	/* Occurs every 1 ms (uncomment LED toggle code below to test) */
	TGL_PORT(PORTB, PORTB5);

	uint16_t adc_value = ADC;

	if(!complete_sampling){
		if (current_adc_channel == ADC_CH_VOLTAGE) {
			adc_voltages[adc_voltages_head] = adc_convert(adc_value);
			adc_voltages_t[adc_voltages_head] = miliseconds+MILISECOND_DELAY;
			++adc_voltages_head;

			/* Switch the channel of the next sample */
			adc_set_channel(ADC_CH_CURRENT);
		} else {
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
		timer0_stop();
		complete_sampling = 1;
		adc_currents_head = 0;

		set_elapsed_cycle();

		/* Copy array values so it's not overwritten during calculation AND debug printing */

/*		THIS IS FASTER THEN memcpy() BY ~ 102 us

		raw_voltages[0] = adc_voltages[0];
		raw_voltages[1] = adc_voltages[1];
		raw_voltages[2] = adc_voltages[2];
		raw_voltages[3] = adc_voltages[3];
		raw_voltages[4] = adc_voltages[4];
		raw_voltages[5] = adc_voltages[5];
		raw_voltages[6] = adc_voltages[6];
		raw_voltages[7] = adc_voltages[7];
		raw_voltages[8] = adc_voltages[8];
		raw_voltages[9] = adc_voltages[9];
*/
		memcpy((void *) raw_voltages, (void *) adc_voltages, sizeof (adc_voltages));
		memcpy((void *) raw_voltages_t, (const void *) adc_voltages_t, sizeof (adc_voltages_t));

		memcpy((void *) raw_currents, (void *) adc_currents, sizeof (adc_currents));
		memcpy((void *) raw_currents_t, (const void *) adc_currents_t, sizeof (adc_voltages_t));
	}
}

#endif /* 0 */

void adc_on()
{
	SET_PORT(ADCSRA, ADEN);
}

void adc_off()
{
	CLR_PORT(ADCSRA, ADEN);
}
