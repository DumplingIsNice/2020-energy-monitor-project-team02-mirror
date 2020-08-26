/*
* uart.c
*
* Created: 21/08/2020 09:47:00 PM
* Author: Hao Lin
*
* Functions to do with communicating over the UART protocol
*/

#include "common.h"
#include <util/delay.h> // Needed to use _delay_ms()

#define SPACE 0x20
#define COMMA 0x2C
#define ZERO 0x30

static void ascii_convert(uint16_t *number)
{ // Converts a unsigned number digit to ascii format. Author: Hao Lin (22/08/2020)
	*number += 48;
}

static void extract_digits(uint16_t number, uint16_t *ones, uint16_t *tens, uint16_t *hundreds)
{ // Extracts digits of a number below 1000. Author: Hao Lin (22/08/2020)
	*ones = number % 10;
	*tens = (number % 100 - *ones) / 10;
	*hundreds = (number - *tens * 10 - *ones) / 100;
}

// Function to extract tenths place (1st digit after decimal place)
static void extractTenths(float data, uint16_t *tenths) {
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

// Function to extract hundredths place (2nd digit after decimal place)
static void extractHundredths(float data, uint16_t *hundredths) {
	uint16_t ones = 0, tens = 0, hundreds = 0, tenths = 0;
	extract_digits(data, &ones, &tens, &hundreds);
	extractTenths(data, &tenths);

	if (data < 10) {
		data = (data - ones) * 100;
		*hundredths = (int) (data - (tenths));
	}

	else if (data > 10 && data < 100) {
		data = ((data - (tens*10) - ones) * 100);
		*hundredths = (int) (data - (tenths));
	}

	else if (data > 100 && data < 1000) {
		data = (data - (hundreds*100) - (tens*10) - ones) * 100;
		*hundredths = (int) (data - (tenths));
	}

}

void usart_init(uint16_t ubrr)
{ // UART init function. Author: Hao Lin (21/08/2020)

	/*UDR0 = 0b00000000;*/
	UCSR0A = 0b00000000;

	UCSR0B |= (1 << TXEN0) & ~(1 << UCSZ02); // Set TXEN0 bit to 1 (enable transmit) and UCSZ02 bit to 0 (8 data bits)
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00); // UMSEL0[1..0]=00 (UART mode), UPM0[1..0]=00 (no parity), USBS0=0 (1 stop-bit), UCSZ0[1..0]=11 (8 data bits)
	UBRR0 = ubrr;

	// UBRR0 = ((F_CPU / (16*baud)) - 1); // Full eqn for ubrr value.
}

void usart_transmit(uint8_t data)
{ // UART character transmit function. Author: Krithik Lekinwala (21/08/2020)
	while ((UCSR0A & (1 << UDRE0)) == 0) { // Continuously checking to see if UDRE0 bit is 0
		// If it is not 0, wait until it is so it starts writing the data to the register

	}
	UDR0 = data; // Writing data to register
}

void usart_transmit_raw(uint8_t rawData[], size_t arraySize)
{

	//size_t totalBytes = sizeof(rawData)/sizeof(rawData[0]); // Returns size of the array input
	for (size_t i = 0; i < arraySize; i++) {
		usart_transmit(rawData[i]);
	}
	// UDR0 = data; // Writing data to register
}

void usart_string(char s[])
{
	int i;
	for (i = 0; s[i] != '\0'; ++i) ;
	usart_transmit_raw((unsigned char *) s, i);
}

void print_float(float data) {
	
	uint16_t ones = 0, tens = 0, hundreds = 0, tenths = 0, hundredths = 0;
	
	extractTenths(data, &tenths);
	extractHundredths(data, &hundredths);
	
	extract_digits(data, &ones, &tens, &hundreds);
	
	ascii_convert(&ones);
	ascii_convert(&tens);
	ascii_convert(&hundreds);
	ascii_convert(&tenths);
	ascii_convert(&hundredths);
	

	if (hundreds != ZERO) {
		usart_transmit(hundreds);
	}

	if (tens != ZERO) {
		usart_transmit(tens);
	}

	usart_transmit(ones);
	usart_transmit(46); // Transmitting decimal point
	usart_transmit(tenths);
	usart_transmit(hundredths);
	
} 


//Transmits a single positive integer with no other formatting
void print_integer(uint16_t x)
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

// Print out an array of POSITIVE integers.
// Inputs will be array of type int, and length of the array.
// NOTE: the function should convert the numbers to ASCII before sending them over UART.
// Author: Hao Lin (22/08/20)
void print_array_intergers(uint16_t intArray[], uint16_t arrayLength)
{

	uint16_t number;
	uint16_t ones = 0, tens = 0, hundreds = 0, i = 0;

	while (1) {

		number = intArray[i];

		print_integer(number);

		i++;

		if (i >= arrayLength) {
			break;
		}
		usart_transmit(COMMA);
		usart_transmit(SPACE);
	}
	
}
