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

void usart_init(uint32_t ubrr); // Initializes USART registers by specification and ubrr value. Author: Hao Lin (21/08/2020)

#endif /* UART_H */
