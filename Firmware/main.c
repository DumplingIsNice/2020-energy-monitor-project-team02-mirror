
/* Local Includes */
#include "common.h"
#include "uart.h"
#include "adc.h"
#include "timer0.h"
#include "timer2.h"
#include "dsp.h"

/* AVR Includes */
#include <avr/io.h>
#include <avr/interrupt.h>


/* #define ENABLE_TESTING */

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
	timer2_init();
	voltage_zc_interrupt_init();

	/* Globally Enable Interrupts */
	sei();

	while (1) {
		if (currently_sampling >= 2) {
			/* Calculating RMS Voltage */
			adc2real_voltage();
			cubic_interpolate();
			calculate_rms_voltage();

			/* Calculating Power */
			adc2real_current();
			cubic_interpolate();
			calculate_power();
			calculate_energy();

			/* Get peak current */
			calculate_pk_current();

			print("%f V(RMS)\r", rms_voltage);
			print("%f A\r", pk_current);
			print("%f W\r", power);
			print("%f J\r", energy);
			print("%f\r\r", period_ms * 1e-3);

			currently_sampling = 0;
			cycle_count = 0;
			ENABLE_ZERO_CROSSING;
		}
	}

	return 0;
}

