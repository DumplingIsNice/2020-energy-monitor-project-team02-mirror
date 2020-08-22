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

void usart_transmit(uint8_t data) { // UART character transmit function. Author: Krithik Lekinwala (21/08/2020)
	while ((UCSR0A & (1<<UDRE0)) == 0) { // Continuously checking to see if UDRE0 bit is 0
		// If it is not 0, wait until it is so it starts writing the data to the register
		
	}
	UDR0 = data; // Writing data to register
	
}

void usart_transmitRaw(uint8_t rawData[], size_t arraySize) {
	while ((UCSR0A & (1<<UDRE0)) == 0) { // Continuously checking to see if UDRE0 bit is 0
		// If it is not 0, wait until it is so it starts writing the data to the register
		
	}
	
	//size_t totalBytes = sizeof(rawData)/sizeof(rawData[0]); // Returns size of the array input
	for (int i = 0; i < arraySize; i++ ) {
		UDR0 = rawData[i];
	}
	// UDR0 = data; // Writing data to register
}

void ascii_convert(uint16_t *number){ // Converts a unsigned number digit to ascii format. Author: Hao Lin (22/08/2020)
	*number += 48;
}

void extract_digits(uint16_t number, uint16_t *ones, uint16_t *tens, uint16_t *hundreds){ // Extracts digits of a number below 1000. Author: Hao Lin (22/08/2020)
	*ones = number%10;
	*tens = (number%100 - *ones)/10;
	*hundreds = (number - *tens*10 - *ones)/100;
}
