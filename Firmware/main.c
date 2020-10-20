
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
	DDRB = 0xFF;

	/* Initalisation code */
	usart_init();
	adc_init();
	timer0_init();
/*	timer2_init(); */
	Disp_Init();
	voltage_zc_interrupt_init();

	/* Globally Enable Interrupts */
	sei();

	while (1) {
		if (!currently_sampling && !enable_zc) {
			period_ms = 40;
			adc2real_voltage();
			adc2real_current();
			cubic_interpolate();

			calculate_pk_current();
			calculate_power();
			calculate_energy();
			calculate_rms_voltage();

			print("%f V(RMS)\r", rms_voltage);
			print("%f A\r", pk_current);
			print("%f W\r", power);
			print("%f J\r", energy);
			print("%f\r\r", period_ms * 1e-3);

			enable_zc = 1;
		}
	}

	return 0;
}

