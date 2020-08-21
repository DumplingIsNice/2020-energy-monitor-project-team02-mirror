/*
* uart.c
*
* Created: 21/08/2020 09:47:00 PM
* Author: Hao Lin
*
* Functions to do with communicating over the UART protocol
*/

#include "common.h"

void usart_init(uint32_t ubrr){ // UART init function. Author: Hao Lin (21/08/2020)

	UDR0 = 0b00000000;
	UCSR0A = 0b00000000;

	UCSR0B |= (1<<TXEN0) & ~(1 << UCSZ02); // Set TXEN0 bit to 1 (enable transmit) and UCSZ02 bit to 0 (8 data bits)
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00); // UMSEL0[1..0]=00 (UART mode), UPM0[1..0]=00 (no parity), USBS0=0 (1 stop-bit), UCSZ0[1..0]=11 (8 data bits)
	UBRR0 = ubrr;

	// UBRR0 = ((F_CPU / (16*baud)) - 1); // Full eqn for ubrr value.
}