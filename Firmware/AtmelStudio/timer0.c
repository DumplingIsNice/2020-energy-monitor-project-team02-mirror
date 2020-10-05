#include "timer0.h"
#include "adc.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

// Declaring global variables
uint16_t zeroCrossingTimes = 0;
uint16_t timePassed = 0;


// Sample ADC channel when interrupt is triggered every 1ms
ISR(TIMER0_COMPA_vect) { 
	timePassed++;
	uint16_t adc0 = adc_read(0);
	uint16_t adc1 = adc_read(1);
	uint16_t adc2 = adc_read(2);
}


// ISR For INT0
ISR(INT0_vect) {
	zeroCrossingTimes++; // Incrementing amount of zero crossings
	TCCR0B = 0b00000010; // Setting prescaler to 8 for 1ms interrupts
}



// Counts every 1ms 
void timer0_init()
{
	
	TCCR0A = 0b00000010; // Setting to CTC mode
	TCCR0B = 0b00000000; // Set prescaler of 64
	TIMSK0 = 0b00000010; // Setting interrupt on output compare match A
	EIMSK = 0b00000001; // Trigger for INT0
	EICRA = 0b00000001; // Trigger on rising edge, stop on falling edge (i.e, trigger in any change)
	OCR0A = 99; // Required for 1ms accuracy
}


// Checks and resets the timer0 compare match flag
bool timer0_checkAndClearCompare()
{
	// Checking compare match flag value
	if((TIFR0 & (1 << 1 )) != 0) {
		
		// Reset timer overflow flag
		TIFR0 |= (1 << 1);
		return true;
	}
	return false;
}