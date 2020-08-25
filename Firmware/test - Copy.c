#include "common.h"
#include "uart.h"
#include "adc.h"
/* Testing for uart.c */
static void test_uart()
{
	int i = 0;
	char *s1 = "--- BEGIN TESTING ---\r\n";
	usart_init(UBRR);
	usart_transmit('T');
	for (i = 0; s1[i] != '\0'; ++i)
		usart_transmit(s1[i]);
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
/*
	test_common();
	test_adc();
*/
	/*print("--- TESTING COMPLETE ---\n");*/
}