#include <avr/io.h>

#include "common.h"
#include "uart.h"
#include "adc.h"

#define ENABLE_TESTING
int main()
{
#ifdef ENABLE_TESTING
	extern void test_function();
	test_function();
#endif /* ENABLE_TESTING */

	while (1) {
		//terminal_print;
		//_delay_ms(1000);
	}

	return 0;
}



void terminal_print(float rmsV, uint16_t current, float power){

	print("RMS Voltage is: %d \n", rmsV);
	
	print("Peak Current is: %d \n", current);
	
	print("Power is: %d \n", power);
}

