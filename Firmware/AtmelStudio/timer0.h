/*
* timer0.h
*
* Created: 4/10/2020
* Author: Krithik Lekinwala
*
* Functions to do with Timers and timer protocols
*/


#ifndef TIMER0_H_
#define TIMER0_H_
#include <stdbool.h>

/* TIMER0 */

//Initialise Timer0
void timer0_init();


/*  Uses interrupts to check if the ZC (zero crossing) count has reached the 
*	value for 1 period. If so, the flag will be set and a time variable is incremented,
*	keeping track of how long 1 period is. */
bool timer0_checkAndClearCompare();

#endif