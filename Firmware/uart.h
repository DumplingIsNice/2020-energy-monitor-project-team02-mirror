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

// Macros

#define UART_BPS 9600UL // Baud rate / Bits Per Second value the UART module is configured to (_9600 BPS_)
#define UBRR 4 // Prescaler value for initializing baud rate.

// Functions

void usart_init(uint32_t ubrr); // Initializes USART registers by specification and ubrr value. Author: Hao Lin (21/08/2020)
void usart_transmit(uint16_t data); // Defining function to transmit 1 character at a time. Author: Krithik Lekinwala (22/08/2020)
void usart_transmitRaw(uint8_t rawData[], size_t arraySize); // Defining function to transmit single raw bytes one at a time. Author: Krithik Lekinwala (22/08/2020)
void ascii_convert(uint16_t *number); // Converts a unsigned number digit to ascii format. Author: Hao Lin (22/08/2020)

#endif /* UART_H */
