/*
* uart.h
*
* Created: 21/08/2020 09:47:00 PM
* Author: Ankush Patel, Hao Lin
*
* Functions to do with communicating over the UART protocol
*/

#ifndef UART_H
#define UART_H

#include <stdint.h>

// Macros

#define UART_BPS 9600UL // Baud rate / Bits Per Second value the UART module is configured to (_9600 BPS_)
#define UBRR 4 // Prescaler value for initializing baud rate.

/* Connivance macros for printing some control characters */

#define WIN32_NEWLINE
#ifdef WIN32_NEWLINE /* Windows (and this, Proteus) Needs this to show a newline */
#define USART_NEWLINE usart_transmit('\r'); usart_transmit('\n');
#else
#define USART_NEWLINE usart_transmit('\n');
#endif /* WIN32_NEWLINE */

#define USART_TAB usart_transmit('\t');

// Functions

/* MISC */
void usart_init(uint16_t ubrr); // Initializes USART registers by specification and ubrr value. Author: Hao Lin (21/08/2020)
void usart_transmit(uint8_t data); // Defining function to transmit 1 character at a time. Author: Krithik Lekinwala (22/08/2020)
void usart_transmit_raw(uint8_t rawData[], size_t arraySize); // Defining function to transmit single raw bytes one at a time. Author: Krithik Lekinwala (22/08/2020)

/* Sending Strings */
void usart_string(char s[]);

/* Sending Numbers */
void print_integer(uint16_t x);
void print_array_intergers(uint16_t intArray[], uint16_t arrayLength); // Print out an array of POSITIVE integers. Inputs will be array of type int, and length of the array. Author: Hao Lin (22/08/2020)
#endif /* UART_H */
