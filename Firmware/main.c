#include <avr/io.h>

#include "common.h"
#include "uart.h"
#include "adc.h"
#include <util/delay.h>

//#define ENABLE_TESTING
#define RMSVoltage 14.5
#define PeakCurrent 125
#define Power 1.60


void terminal_print(float Vrms, uint16_t Ipeak, float P){

	print("RMS Voltage is: %f \n", RMSVoltage);
	print("Peak Current is: %d \n", PeakCurrent);
	print("Power is: %f \n\r", Power);
}

int main()
{
#ifdef ENABLE_TESTING
	extern void test_function();
	test_function();
#endif /* ENABLE_TESTING */
	usart_init(UBRR);
	while (1) {
		terminal_print(RMSVoltage, PeakCurrent, Power);
		_delay_ms(1000);
	}

	return 0;
}





