
/* Local Includes */
#include "common.h"
#include "uart.h"
#include "adc.h"
#include "timer0.h"
#include "dsp.h"

/* AVR Includes */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


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
	voltage_zc_interrupt_init();

	/* Globally Enable Interrupts */
	sei();

	while (1) {
		int i = 0;
		if (complete_sampling) {
			reverse_voltage_gain();
			reverse_current_gain();
			print("V;");
			for (i = 0; i < RAW_ARRAY_SIZE; ++i) {
				print("  %f ms, %f V", raw_voltages_t[i], raw_voltages[i]);
			}
			print("\nC");
			for (i = 0; i < RAW_ARRAY_SIZE; ++i) {
				print("  t %f ms, %f A", adc_currents_t[i], adc_currents[i]);
			}
			print("T %d ms", get_period());
			print("\n -");
		}
	}

	return 0;
}

