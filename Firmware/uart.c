/*
*	uart.c
*
*	Created: 21/08/2020 09:47:00 PM
*	Author: Hao Lin
*
*	Functions to do with communicating over the UART protocol
*/

#include "common.h"

#define UART_BPS 9600UL // Baud rate / Bits Per Second value the UART module is configured to (_9600 BPS_)
#define UBRR ((F_CPU / (UART_BPS * 16)) - 1) // Prescaler value for initializing baud rate.

//	Defines of common ASCII transmission characters in HEX
#define SPACE 0x20
#define COMMA 0x2C
#define ZERO 0x30


//	Converts a single unsigned number digit to ascii format. Author: Hao Lin (22/08/2020)
static void ascii_convert(uint16_t *number)
{ 
	*number += 48;
}


//	Extracts digits of a number below 1000. Author: Hao Lin (22/08/2020)
static void extract_digits(uint16_t number, uint16_t *ones, uint16_t *tens, uint16_t *hundreds)
{ 
	*ones = number % 10;
	*tens = (number % 100 - *ones) / 10;
	*hundreds = (number - *tens * 10 - *ones) / 100;
}


/*	Function to extract tenths place (1st digit after decimal place). Takes data and pointer to tenths variable.
*	Defined as a static function because we do not use it outside of this file.
*/
static void extractTenths(float data, uint16_t *tenths)
{
	uint16_t ones = 0, tens = 0, hundreds = 0;
	extract_digits(data, &ones, &tens, &hundreds);

	if (data < 10) {
		 *tenths = (int) ((data - ones) * 10);
	}

	else if (data > 10 && data < 100) {
		 *tenths = (int) ((data - (tens*10) - ones) * 10);
	}

	else if (data > 100 && data < 1000) {
		 *tenths = (int) ((data - (hundreds*100) - (tens*10) - ones) * 10);
	}
}


/*	Function to extract hundredths place (2nd digit after decimal place), taking the data and the pointer to hundredths as an input.
*	Defined as a static function because we do not use it outside of this file.
*/
static void extractHundredths(float data, uint16_t *hundredths)
{
	uint16_t ones = 0, tens = 0, hundreds = 0, tenths = 0;
	extract_digits(data, &ones, &tens, &hundreds);
	extractTenths(data, &tenths);

	if (data < 10) {
		data = (data - ones) * 100;
		*hundredths = (int) (data - (tenths*10));
	}

	else if (data > 10 && data < 100) {
		data = ((data - (tens*10) - ones) * 100);
		*hundredths = (int) (data - (tenths*10));
	}

	else if (data > 100 && data < 1000) {
		data = (data - (hundreds*100) - (tens*10) - ones) * 100;
		*hundredths = (int) (data - (tenths*10));
	}

}


/*	UART initialisation function, sets the bits for registers A, B and C to enable transmit, specify stop bit, bits to transmit, and UART mode.
*	UCSR0B:
*		> Set TXEN0 bit to 1 (enable transmit) and UCSZ02 bit to 0 (8 data bits)
*
*	UCSR0C:
*		> UMSEL0[1..0]=00 (UART mode), UPM0[1..0]=00 (no parity), USBS0=0 (1 stop-bit), UCSZ0[1..0]=11 (8 data bits)
*
*	Finally, we calculate the ubbr value and set it in the Baud Rate register (UBRR0). Baud Rate = 9600 and frequency of 800kHz
*	EQUATION: UBRR0 = ((F_CPU / (16*baud)) - 1);
*/
void usart_init()
{

	UCSR0A = 0b00000000;

	UCSR0B |= (1 << TXEN0) & ~(1 << UCSZ02);
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
	UBRR0 = UBRR;

}


/*	UART primary transmit function (used further in other functions)
*	While loop checking to see if UDRE0 bit is 0 and write to the data register if it is.
*/
void usart_transmit(uint8_t data)
{ 
	
	while ((UCSR0A & (1 << UDRE0)) == 0) { // 

	}
	UDR0 = data; // Writing data to register
	
}

//	Transmits, raw (unfiltered) data with an array and arraySize as input
void usart_transmit_raw(uint8_t rawData[], size_t arraySize)
{

	for (size_t i = 0; i < arraySize; i++) {
		usart_transmit(rawData[i]);
	}
	
}


/*	Prints a string of character arrays. We use the raw transmit function to do this by iterating
*	through each array character.
*/
void usart_print_string(char s[])
{
	int i;
	for (i = 0; s[i] != '\0'; ++i) ;
	usart_transmit_raw((unsigned char *) s, i);
}


/*	Function that rounds a float data input to 3 significant figures.
*	Extracts the digits via extract_digits() function (hundreds, tens, ones, tenths, hundredths)
*	Converts the characters to ascii via ascii_convert()
*	Then, transmits the data with a decimal point.
*/
void usart_print_float(float data) {
	uint16_t ones = 0, tens = 0, hundreds = 0, tenths = 0, hundredths = 0;

	/* Handle / Deal with Negative Numbers */
	if (data < 0) {
		usart_transmit('-');
		data = -data; /* Now make it positive and proceed as normal */
	}

	extractTenths(data, &tenths);
	extractHundredths(data, &hundredths);

	extract_digits(data, &ones, &tens, &hundreds);

	ascii_convert(&ones);
	ascii_convert(&tens);
	ascii_convert(&hundreds);
	ascii_convert(&tenths);
	ascii_convert(&hundredths);

	if (tens == ZERO) {
		usart_transmit(ones);
		usart_transmit('.');
		usart_transmit(tenths);
		usart_transmit(hundredths);
	} else {
		usart_transmit(hundreds);
		usart_transmit(tens);
		usart_transmit(ones);
		usart_transmit('.');
		usart_transmit(tenths);
	}

}


/*	Transmits a single positive integer with no other formatting
*	Extracts the digits then converts into ASCII text (for transmission)
*	Conditionals to check which place values to transmit first.
*/
void usart_print_integer(uint16_t x)
{
	uint16_t ones = 0, tens = 0, hundreds = 0;
	extract_digits(x, &ones, &tens, &hundreds);
	
	ascii_convert(&ones);
	ascii_convert(&tens);
	ascii_convert(&hundreds);
	
	if (hundreds > ZERO){
		usart_transmit(hundreds);
	}
	
	if (tens > ZERO || hundreds > ZERO){
		usart_transmit(tens);
	}
	
	usart_transmit(ones);
}


/*	Print out an array of POSITIVE integers.
*	Inputs will be array of type int, and length of the array.
*	NOTE: the function should convert the numbers to ASCII before sending them over UART.
*	Author: Hao Lin (22/08/20)
*/
void usart_print_array_intergers(uint16_t intArray[], uint16_t arrayLength)
{
	uint16_t number;
	uint16_t i = 0;

	while (1) {
		
		number = intArray[i];
		usart_print_integer(number);
		i++;
		
		if (i >= arrayLength) {
			break;
		}
		
		usart_transmit(COMMA);
		usart_transmit(SPACE);
	}
	
}
