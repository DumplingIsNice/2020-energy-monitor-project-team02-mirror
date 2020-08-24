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

	}

	return 0;
}
