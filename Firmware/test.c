#include "common.h"
#include "uart.h"
#include "adc.h"

/* Testing for uart.c */
static void test_uart()
{
	int i;

	usart_init(UBRR);
	for (i = 0; "--- BEGIN TESTING ---\n"[i] != '\0'; ++i )
		usart_transmit("--- BEGIN TESTING ---"[i]);
	for (i = 0; "--- TESTING UART ---\n"[i] != '\0'; ++i )
		usart_transmit("\n--- TESTING UART ---\n"[i]);
}

/* Testing for common.c */
static void test_common()
{
	print("--- TESTING COMMON ---\n");
}

/* Testing for adc.c */
static void test_adc()
{

}

void test_function()
{
	test_uart();
	test_common();
	test_adc();

	print("--- TESTING COMPLETE ---\n");
}

