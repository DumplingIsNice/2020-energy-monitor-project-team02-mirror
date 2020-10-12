#include <stdarg.h>
#include <stddef.h>
#include "common.h"
#include "uart.h"

/*
 * Round the floating point number n to the number of decimal places specified.
 * Note that decimalPlace = 0 means round to nearest int.
 *
 * Also note inaccuracies due to floating point representation
 * 	e.g. fround(123.67) = 123.69999 not 123.7 as expected.
 */
float fround(float n, int decimalPlace)
{
	float f = 0;

	switch (decimalPlace) {
	case 0:
		/* No rounding, just return int */
		f = (n - (int) n > 0.5 ? (int) n + 1 : (int) n);
		break;
	default:
		f = fround(n * decimalPlace * 10, 0) / decimalPlace * 10;
		break;
	}

	return f;
}

/*
 * fstr is a format string like printf, except it only supports the following
 * specifiers:
 * 	- %s to print a string
 * 	- %f to print a float
 * 	- %u or %d to print an unsigned int
 *	- %x to print an unsigned int in hex
 * 	- %hhd to print a byte
 * 	- %hhx to print a byte in hex
 */
void print(char fstr[], ...)
{
	unsigned int u;
	float f;
	char *s;

	size_t i;
	va_list vaargs;

	va_start(vaargs, fstr);
	for (i = 0; fstr[i] != '\0'; ++i) {
		switch (fstr[i]) {
		case '%':
			++i;
			switch (fstr[i]) {
			case '%':
				usart_transmit('%');
				break ;
			case 's':
				s = va_arg(vaargs, char *);
				usart_print_string(s);
				break ;
			case 'd':
			case 'u':
				u = va_arg(vaargs, unsigned);
				usart_print_integer(u);
				break ;
			case 'x':
				u = va_arg(vaargs, unsigned);
				/* TODO: when uart function to send single int as hex is created, call it here */
				break ;
			case 'f':
				f = va_arg(vaargs, double);
				usart_print_float(f);
				break ;
			}
			break ;
		default:
			usart_transmit(fstr[i]);
			break ;
		}
	}

	va_end(vaargs);

	USART_NEWLINE;
}
