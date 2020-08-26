#include "common.h"
#include "uart.h"
#include "adc.h"
/* Testing for uart.c */
static void test_uart()
{
	int i = 0;
	uint16_t intArray[] = {0, 1, 10, 100, 1000, 10000};

	usart_init(UBRR);

	/* Testing sending characters */
	for (i = 0; "--- BEGIN TESTING ---\r\n"[i] != '\0'; ++i)
		usart_transmit("--- BEGIN TESTING ---\r\n"[i]);

	for (i = 0; "  * TESTING UART---\r\n"[i] != '\0'; ++i)
		usart_transmit("  * TESTING UART---\r\n"[i]);


	/* Testing Sending Ints */
	for (i = 0; "  * Testing Printing Ints---\r\n"[i] != '\0'; ++i) {
		usart_transmit("  * Testing Printing Ints---\r\n"[i]);
	}
	print_integer(10);
	usart_transmit(' ');
	print_integer(0);
	usart_transmit(' ');
	print_integer(1);
	usart_transmit(' ');
	print_integer(579);
	usart_transmit(' ');

	/* Printing an array of integers */
	for (i = 0; "\r\n  * Testing Printing Array Of Ints---\r\n"[i] != '\0'; ++i) {
		usart_transmit("\r\n  * Testing Printing Array Of Ints---\r\n"[i]);
	}
	print_array_intergers(intArray, sizeof (intArray));

	/* Printing Floating Points */
	for (i = 0; "\r\n  * Testing Printing Floats---\r\n"[i] != '\0'; ++i) {
		usart_transmit("\r\n  * Testing Printing Floats---\r\n"[i]);
	}
	print_float(10);
	usart_transmit(' ');
	print_float(0);
	usart_transmit(' ');
	print_float(1);
	usart_transmit(' ');

	print_float(0.0);
	usart_transmit(' ');
	print_float(1.0);
	usart_transmit(' ');
	print_float(1.1);
	usart_transmit(' ');
	print_float(5.8);
	usart_transmit(' ');
	print_float(84.83);
	usart_transmit(' ');
	print_float(0.00);
	usart_transmit(' ');
	print_float(06.04);
	usart_transmit(' ');
	print_float(4.80);
	usart_transmit(' ');
	print_float(0.08);

}
/* Testing for common.c */
static void test_common()
{
	print("\r\n--- TESTING COMMON ---\r\n");
	print("This is a test to print a formated string. Int: %d, Int: %u, Float: %f\n", 10, 50, 10.23);
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
