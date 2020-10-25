/*
* timer0.h
*
* Created: 4/10/2020
* Author: Krithik Lekinwala, Hao Lin
*
* Functions regarding timer0 peripherals and protocols
*/

#ifndef TIMER0_H_
#define TIMER0_H_

/* TIMER0 */

extern volatile uint16_t period_ms;

void timer0_init();
void timer0_reset();
void timer0_stop();

#endif
