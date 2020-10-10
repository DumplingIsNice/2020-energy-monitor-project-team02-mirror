#include "common.h"
#include "timer0.h"
#include <avr/interrupt.h>

uint16_t miliseconds;

ISR(TIMER0_COMPA_vect) { if (++miliseconds >= RAW_ARRAY_SIZE * 2) miliseconds = 0;}

// Counts every 1ms
void timer0_init()
{
	SET_PORT(TCCR0A, WGM01); /* Setting to CTC mode */

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

	/* Setting interrupt on output compare match A */
	SET_PORT(TIMSK0, OCIE0A);
}

void timer0_start()
{
	/* Selects clock*/
	
	#ifdef HARDWARE_BUILD
	/* Set prescaler of 128 */
	SET_PORT(TCCR0B, CS22), SET_PORT(TCCR0B, CS20);
	#else
	/* Set prescaler of 8 */
	SET_PORT(TCCR0B, CS21);
	#endif /* HARDWARE_BUILD */
	miliseconds = 0;
}

void timer0_stop()
{
	/* Select no clock */
	CLR_PORT(TCCR0B, CS02), CLR_PORT(TCCR0B, CS01), CLR_PORT(TCCR0B, CS00);
}