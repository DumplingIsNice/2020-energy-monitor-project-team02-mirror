/* Energy Monitor Main for ATmega328PB */

/* Local Includes */
#include "common.h"
#include "uart.h"
#include "adc.h"
#include "timer0.h"
#include "timer2.h"
#include "dsp.h"
#include "display.h"

/* AVR Includes */
#include <avr/io.h>
#include <avr/interrupt.h>


/* #define ENABLE_TESTING */
volatile unsigned enable_zc = 1;

int main()
{
#ifdef ENABLE_TESTING
	extern void test_function();
	test_function();
#endif /* ENABLE_TESTING */
	unsigned sampeled_voltage_current = 0;

	DDRB = 0xFF;

	/* Initalisation code */
	usart_init();
	adc_init();
	timer0_init();
	timer2_init();
	disp_init();
	voltage_zc_interrupt_init();

	/* Globally Enable Interrupts */
	sei();

	while (1) {
		if (!currently_sampling && !enable_zc) {
			if (sampeled_voltage_current) {
				adc2real_voltage();
				adc2real_current();
				cubic_interpolate();

				calculate_power();
				calculate_energy();
				calculate_pk_current();
				calculate_rms_voltage();

				print("%f V(RMS)\r\n", rms_voltage);
				print("%f A(PK)\r\n", pk_current);
				print("%f W\r\n", power);
				print("%f J\r\n", energy);

				sampeled_voltage_current = 0;
				enable_zc = 1;
			} else { /* We still need to sample current */
				sampeled_voltage_current = enable_zc = 1;
			}
		}
		if(change_display){
			disp_next_value();
		}
	}

	return 0;
}

