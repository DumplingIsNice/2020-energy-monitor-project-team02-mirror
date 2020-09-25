#include <avr/io.h>

#include "common.h"
#include "uart.h"
#include "adc.h"
#include <util/delay.h>


// ADC initialisation
void adc_init() {
    ADMUX = 0b01000000;
    ADCSRA = 0b10000101; // 32 prescaler and auto trigger
    ADCSRB = 0b00000000; // Timer0 trigger, not using timers right now so all disabled
    DIDR0 = 0b00000000; // Buffers are not disabled
}


// This function reads an ADC channel and return results​
uint16_t adc_read(uint8_t channel) {
	ADMUX &= 0xF0; // Clear channel selection
	ADMUX |= channel; // Set channel to convert
	
	ADCSRA |= (1<<ADSC); // Start ADC conversion
	
	//ADIF bit is checked to see if it is 0
	//If ADIF bit is not 0, wait until it becomes 0
	while ((ADCSRA & (1 << ADIF)) == 0) { 
		;
	}
	
	return ADC;
}


// Convert a single adcCount input and return voltage
float adc_convert(uint16_t adcCount) {
	float voltage = (5*adcCount)/(float)1024;
	return voltage;
}
