#include "common.h"
#include "uart.h"
#include "adc.h"
/* Testing for uart.c */
static void test_uart()
{
	int i = 0;

	usart_init(UBRR);

	for (i = 0; "--- BEGIN TESTING ---\r\n"[i] != '\0'; ++i)
		usart_transmit("--- BEGIN TESTING ---\r\n"[i]);

	for (i = 0; "\tTESTING UART---\r\n"[i] != '\0'; ++i)
		usart_transmit("  TESTING UART---\r\n"[i]);
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
