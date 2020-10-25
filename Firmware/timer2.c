/*
* timer2.c
*
* Created: 20/10/2020
* Author: Hao Lin
*
* Functions regarding timer2 peripherals and protocols
*/

#include "common.h"
#include "timer2.h"
#include "display.h"
#include <avr/interrupt.h>

volatile uint16_t timer2_miliseconds;
volatile uint8_t change_display = 0;

/* TIMER2 */

ISR(TIMER2_COMPA_vect)
{
	/* Use this LED to check if interrupt is called. */
	//TGL_PORT(PORTB, PORTB5);

	/* 10ms Refresh */
	if (timer2_miliseconds >= 100){ // 1s
		//TGL_PORT(PORTB, PORTB5); // Use this LED to check if values are cycled every 1s
		change_display = 1;
		timer2_miliseconds = 0;
	} else {
		disp_scan_next();
		++timer2_miliseconds;
	}

	/* 40ms Refresh */
	/*
	if (timer2_miliseconds >= 25){ // 1s

		change_display = 1;
		timer2_miliseconds = 0;
	} else {
		disp_scan_next();
		++timer2_miliseconds;
	}
	*/
}

void timer2_init()
{
		SET_PORT(TCCR2A, WGM21); /* Setting to CTC mode */

	#ifdef HARDWARE_BUILD
		/* Set prescaler of 128 */
		SET_PORT(TCCR2B, CS22), SET_PORT(TCCR2B, CS21), SET_PORT(TCCR2B, CS20);
		/* overflow at count of 124 for 1 ms */
		OCR2A = 155;
	#else
		/* Set prescaler of 32 (10ms) */
		SET_PORT(TCCR2B, CS20);
		SET_PORT(TCCR2B, CS21);

		/* Set prescaler of 256 (40 ms) */
		//SET_PORT(TCCR2B, CS20);
		//SET_PORT(TCCR2B, CS22);

		/* overflow at count of 249 for 10/40 ms */
		OCR2A = 249;
	#endif /* HARDWARE_BUILD */

		/* Setting interrupt on output compare match A */
		SET_PORT(TIMSK2, OCIE2A);
}

void timer2_stop()
{
	/* Select no clock */
	CLR_PORT(TCCR2B, CS02), CLR_PORT(TCCR2B, CS01), CLR_PORT(TCCR2B, CS00);
}