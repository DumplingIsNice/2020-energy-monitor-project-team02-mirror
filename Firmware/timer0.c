#include "common.h"
#include <avr/interrupt.h>

volatile uint16_t period_ms;

/* Counts every 1ms */
ISR(TIMER0_COMPA_vect) { ++period_ms; }

void timer0_init()
{
	SET_PORT(TCCR0A, WGM01); /* Setting to CTC mode */

	/* Select no clock initially (timer is stopped) and set timer counter to 0 */
	CLR_PORT(TCCR0B, CS02), CLR_PORT(TCCR0B, CS01), CLR_PORT(TCCR0B, CS00);
	TCNT0 = period_ms = 0x00;

	/* Setting interrupt on output compare match A */
	SET_PORT(TIMSK0, OCIE0A);
}

/* Selects clock*/
void timer0_reset()
{

#ifdef HARDWARE_BUILD
	/* Set prescaler of 128 */
	SET_PORT(TCCR0B, CS22), SET_PORT(TCCR0B, CS20);
	/* overflow at count of 124 for 1 ms */
	OCR0A = 124;
#else
	/* Set prescaler of 8 */
	SET_PORT(TCCR0B, CS21);
	/* overflow at count of 99 for 1 ms */
	OCR0A = 99;
#endif /* HARDWARE_BUILD */

	/* reset the timer counter */
	TCNT0 = period_ms = 0x00;
}

/* Select no clock */
void timer0_stop()
{
	CLR_PORT(TCCR0B, CS02), CLR_PORT(TCCR0B, CS01), CLR_PORT(TCCR0B, CS00);
}
