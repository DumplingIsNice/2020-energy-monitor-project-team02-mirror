/*
* adc.c
*
* Created: 25/09/2020
* Author: Krithik Lekinwala
*
* Functions regarding ADC peripherals and protocols
*/

#include "common.h"
#include "timer0.h"
#include "adc.h"
#include "dsp.h"

#include <avr/interrupt.h>

void adc_set_channel(uint8_t channel)
{
	/* Ensure channel selection is reset */
	CLR_PORT(ADMUX, MUX2);
	CLR_PORT(ADMUX, MUX1);
	CLR_PORT(ADMUX, MUX0);
	
	ADMUX |= channel;

	current_adc_channel = channel;
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
	//TGL_PORT(PORTB, PORTB5);
	if (current_adc_channel == ADC_CH_VOLTAGE) {
		adc_voltages[adc_voltages_head++] = ADC;
	} else {
		adc_currents[adc_currents_head++] = ADC;
	}
}
