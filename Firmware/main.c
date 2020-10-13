
/* Local Includes */
#include "common.h"
#include "uart.h"
#include "adc.h"
#include "timer0.h"
#include "dsp.h"

/* AVR Includes */
#include <avr/io.h>
#include <avr/interrupt.h>


/* #define ENABLE_TESTING */

volatile char calc_complete = 0;

int main()
{
#ifdef ENABLE_TESTING
	extern void test_function();
	test_function();
#endif /* ENABLE_TESTING */
	DDRB = 0xFF;
	/* Initalisation code */
	usart_init();
	adc_init();
	timer0_init();
	voltage_zc_interrupt_init();

	/* Globally Enable Interrupts */
	sei();

	while (1) {
		if (complete_sampling && !calc_complete) {
			adc2real_voltage();
			adc2real_current();
			cubic_interpolate();
			calc_complete = 1;
/*
			reverse_voltage_gain();
			reverse_current_gain();
*/
		}
	}

	return 0;
}

