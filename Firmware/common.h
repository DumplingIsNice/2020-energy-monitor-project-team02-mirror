#ifndef COMMON_H
#define COMMON_H

/* Macros for important values. */

/* #define HARDWARE_BUILD */

/* Defining system clock frequency
 * Note that we use a different clock frequency when building for 
 * Proteus (Simulation) and actual hardware ATmega328p
 */
#ifndef HARDWARE_BUILD
#define F_CPU 800000UL /* 800 KHz */
#else
#define F_CPU 16000000UL /* 16 MHz */
#endif /* HARDWARE_BUILD */

// Libraries to include.

#include <stdint.h> // Needed to use size_t and other various types
#include <stdlib.h> // 
#include <avr/io.h> //Needed for using the macros for register addresses


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


/* [Global] Arrays to hold values (defined in common.c) */

#define ADC_CH_VOLTAGE 0
#define ADC_CH_CURRENT 1

extern int current_adc_channel;

#define RAW_ARRAY_SIZE 10
#define CYCLE_SAMPLED 1

extern float raw_voltages[RAW_ARRAY_SIZE];
extern float raw_voltages_t[RAW_ARRAY_SIZE];
extern unsigned raw_voltages_head;

extern float raw_currents[RAW_ARRAY_SIZE];
extern float raw_currents_t[RAW_ARRAY_SIZE];
extern unsigned raw_currents_head;

/*
 * Round the floating point number n to the number of decimal places specified.
 * Note that decimalPlace = 0 means round to nearest int.
 *
 * Also note inaccuracies due to floating point representation
 * 	e.g. fround(123.67) = 123.69999 not 123.7 as expected.
 */
float fround(float n, int decimalPlace);

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
void print(char fstr[], ...);

#endif /* COMMON_H */
