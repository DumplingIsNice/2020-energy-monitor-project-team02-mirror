#include "common.h"
#include "timer2.h"
#include "display.h"
#include <avr/interrupt.h>

volatile uint16_t timer2_miliseconds;

/* TIMER2 */

ISR(TIMER2_COMPA_vect)
{
	//Use this LED to check if interrupt is called.
	//TGL_PORT(PORTB, PORTB5);
	if (timer2_miliseconds >= 100){ // 1s
		disp_next_value();
		timer2_miliseconds = 0;
	} else {
		disp_scan_next();
		++timer2_miliseconds;
	}
}

void timer2_init()
{
		SET_PORT(TCCR2A, WGM21); /* Setting to CTC mode */

	#ifdef HARDWARE_BUILD
		/* Set prescaler of 128 */
		SET_PORT(TCCR2B, CS22), SET_PORT(TCCR2B, CS20);
		/* overflow at count of 124 for 1 ms */
		OCR2A = 124;
	#else
		/* Set prescaler of 64 */
		SET_PORT(TCCR2B, CS20);
		SET_PORT(TCCR2B, CS21);

		/* overflow at count of 248 for 10 ms */
		OCR2A = 248;
	#endif /* HARDWARE_BUILD */

		/* Setting interrupt on output compare match A */
		SET_PORT(TIMSK2, OCIE2A);
}

void timer2_stop()
{
	/* Select no clock */
	CLR_PORT(TCCR2B, CS02), CLR_PORT(TCCR2B, CS01), CLR_PORT(TCCR2B, CS00);
}