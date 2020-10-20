#include "common.h"
#include "timer0.h"
#include "adc.h"
#include "dsp.h"

#include <avr/interrupt.h>

void adc_set_channel(uint8_t channel)
{
	ADMUX &= ~((1 << MUX2) | (1 << MUX1) | (1 << MUX0));
	ADMUX |= channel;
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
	
	adc_pointers[currently_sampling] = ADC;
	++adc_pointers[currently_sampling];
}
