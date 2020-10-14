
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
volatile unsigned enable_zc = 1;
static unsigned sampeled_voltage_current = 0;

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
		if (!currently_sampling && !enable_zc) {
			if (sampeled_voltage_current) {
				unsigned i = 0;
			
				adc2real_voltage();
				adc2real_current();
				cubic_interpolate();
			
				print("raw V\r[");
				for (i = 0; i < RAW_ARRAY_SIZE; ++i) {
					print("%f ", raw_voltages[i]);
				}
				print("]\r");
			
				print("intr V\r[");
				for (i = 0; i < INTERPOLATED_ARRAY_SIZE; ++i) {
					print("%f ", interpolated_voltages[i]);
				}
				print("]\r");

				sampeled_voltage_current = 0;
				enable_zc = 1;
			} else { /* We still need to sample current */
				sampeled_voltage_current = enable_zc = 1;
			}
		}
	}

	return 0;
}

