#include <stdarg.h>
#include <stddef.h>
#include "uart.h"

/*
 * Return the number of characters that would be needed to represent the integer
 * `num` as a string (returned length does NOT include null-terminator) .
 */
static short num_length(int num)
{
	short length = 0;
	if (num < 0) ++length, num *= -1; /* For '-' (negative) sign */
	while (num > 0) ++length, num /= 10;
	return length;
}

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
 * 	- %f to print a float
 * 	- %d to print an int
 * 	- %u to print an unsigned int
 *	- %x to print an unsigned int in hex
 * 	- %hhd to print a byte
 * 	- %hhx to print a byte in hex
 */
void print(char fstr[], ...)
{
	size_t i;
	int d;
	unsigned int u;
	float f;
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
			case 'd':
				d = va_arg(vaargs, int);
				print_integer(d);
				break ;
			case 'u':
				u = va_arg(vaargs, unsigned);
				/* TODO: when uart function to send single int is created, call it here */
				break ;
			case 'x':
				u = va_arg(vaargs, unsigned);
				/* TODO: when uart function to send single int as hex is created, call it here */
				break ;
			case 'f':
				f = va_arg(vaargs, double);
				/* TODO: when uart function to send float is created, call it here */
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
