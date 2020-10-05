#include <avr/io.h>

#include "common.h"
#include "uart.h"
#include "adc.h"
#include <util/delay.h>
#include <avr/interrupt.h>
//#define ENABLE_TESTING
#define RMSVoltage 14.5
#define PeakCurrent 125
#define Power 1.60

int main()
{
#ifdef ENABLE_TESTING
	extern void test_function();
	test_function();
#endif /* ENABLE_TESTING */
	usart_init(UBRR);
	while (1) {
		_delay_ms(1000);
	}

	return 0;
}

