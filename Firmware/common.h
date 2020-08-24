#ifndef COMMON_H
#define COMMON_H

// Macros for important values.

#define F_CPU 800000UL //Defining system clock frequency

// Libraries to include.

#include <avr/io.h> //Needed for using the macros for register addresses
#include <stdint.h> // Needed to use size_t and other various types
#include <stdlib.h> // 


/* Macros to set/clear/toggle bits in a port */
#define SET_PORT(port, bit_n) (port |= (1 << bit_n))
#define CLR_PORT(port, bit_n) (port &= ~(1 << bit_n))
#define TGL_PORT(port, bit_n) (port ^= (1 << bit_n))

/* Macro to read bit from a pin */
#define READ_BIT(pin, bit_n) ((pin & (1 << bit_n)) >> bit_n)

/* Debugging Macro to get current line in file:
 * To use, place _SRC_LOC where you want a string of the form
 * "Current-File:Current-Line-Number"
 */
#define __S1(x) #x
#define __S2(x) __S1(x)
#define _SRC_LOC __FILE__ ":" __S2(__LINE__)

#endif /* COMMON_H */
