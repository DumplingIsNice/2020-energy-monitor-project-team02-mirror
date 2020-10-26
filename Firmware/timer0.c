/*
* timer0.c
*
* Created: 4/10/2020
* Author: Krithik Lekinwala, Hao Lin
*
* Functions regarding timer0 peripherals and protocols
*/

#include "common.h"
#include <avr/interrupt.h>

/* Counts every 1ms */
ISR(TIMER0_COMPA_vect) {}

void timer0_init()
{
	SET_PORT(TCCR0A, WGM01); /* Setting to CTC mode */

	/* Select no clock initially (timer is stopped) and set timer counter to 0 */
	CLR_PORT(TCCR0B, CS02), CLR_PORT(TCCR0B, CS01), CLR_PORT(TCCR0B, CS00);
	TCNT0 = 0x00;

	/* Setting interrupt on output compare match A */
	SET_PORT(TIMSK0, OCIE0A);
}

/* Selects clock*/
void timer0_reset()
{

#ifdef HARDWARE_BUILD
	/* Set prescaler of 64 */
	SET_PORT(TCCR0B, CS01), SET_PORT(TCCR0B, CS00);
	/* overflow at count of 249 for 1 ms */
	OCR0A = 249;
#else
	/* Set prescaler of 8 */
	SET_PORT(TCCR0B, CS01);
	/* overflow at count of 99 for 1 ms */
	OCR0A = 99;
#endif /* HARDWARE_BUILD */

	/* reset the timer counter */
	TCNT0 = 0x00;
}

/* Select no clock */
void timer0_stop()
{
	CLR_PORT(TCCR0B, CS02), CLR_PORT(TCCR0B, CS01), CLR_PORT(TCCR0B, CS00);
}
