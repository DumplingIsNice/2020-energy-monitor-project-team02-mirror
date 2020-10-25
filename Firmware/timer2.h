/*
* timer2.h
*
* Created: 20/10/2020
* Author: Hao Lin
*
* Functions regarding timer2 peripherals and protocols
*/

#ifndef TIMER2_H_
#define TIMER2_H_

/* TIMER2 */

extern volatile unsigned char print_uart;

/* Initialise Timer2 */
void timer2_init();
void timer2_stop();

#endif
