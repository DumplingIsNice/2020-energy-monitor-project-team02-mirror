#include "common.h"
#include "display.h"
#include "dsp.h"
#include "uart.h"

/* Common toggle defines for display and bit shift register */
#define DISABLE_DISPLAYS PORTD |= (0b11110000)
#define ENABLE_DISPLAYS PORTD |= (0b00000000)
#define SHIFT_REG_ON PORTC |= (1<<PORTC5) 
#define SHIFT_REG_OFF PORTC &= ~(1<<PORTC5)

#define DP_APPEND |= (1<<7)
#define PLACE_VALUE_SIZE 4

/* Holds place value digits in an array, calculated using extract functions in UART */
static uint8_t placeValues[4] = {0,0,0,0};
	
/* The current position of the 4-digit number we're displaying */
static volatile uint8_t disp_pos = 4;

/* The current unit we're displaying */
static volatile uint8_t unit = 0;

/* Holds ports for each display (1 - 4 respectively) where displays[0] = Ds1, displays[1] = Ds2 etc */
static uint8_t displays[4] = {(1<<PORTD4), (1<<PORTD5), (1<<PORTD6), (1<<PORTD7)};

/* All potential numbers to display on the seven segment in array form for easy access */
static const uint8_t sevenSegMapping[11] = {
	0b00111111, /* 0 */
	0b00000110, /* 1 */
	0b01011011, /* 2 */
	0b01001111, /* 3 */
	0b01100110, /* 4 */
	0b01101101, /* 5 */
	0b01111101, /* 6 */
	0b00000111, /* 7 */
	0b01111111, /* 8 */
	0b01101111, /* 9 */
	0b10000000,  /* . (decimal point) */
};

/* All potential indicators of the value displayed */
static const uint8_t indicationUnit[4] = 
{
	0b00011100, /* v */
	0b01110111, /* A */
	0b01110011, /* P */
	0b01111001, /* E */
};

void Disp_Send(uint8_t val) {
	// Construct the bit pattern to turn on the segments needed to
	// display number stored in val
	
	init_shift_reg();
	
	uint8_t bit = 0;
	uint8_t dispSequence = val;
	
	// Send the bit pattern to the shift-register
	
	for (int i = 0; i < 8; i++){
		
		bit = (dispSequence & (1 << (7-i))) && 1;
		
		if (bit){
			PORTC |= (1 << PORTC4);
			} else {
			PORTC &= ~(1 << PORTC4);
		}
		toggle_SH_CP();
	}
	
	// Disable all digits
	DISABLE_DISPLAYS;
	
	// Latch the output by toggling SH_ST pin
	toggle_SH_ST();
	
	// Now, depending on the value of disp_pos, enable the correct digit
	// (i.e. set Ds1, Ds2, Ds3 and Ds4 appropriately)
	position_on(disp_pos);
}

void toggle_SH_ST(){
	PORTC ^= (1 << PORTC5);
	PORTC ^= (1 << PORTC5);
}

void toggle_SH_CP(){
	PORTC ^= (1 << PORTC3);
	PORTC ^= (1 << PORTC3);
}

void init_shift_reg(){
	if (!((PORTC & (1 << PORTC3)) && (PORTC & (1 << PORTC5)))){
		PORTC &= (1 << PORTC3) & (1 << PORTC5);
	}
}

/* Display initialisation */
void Disp_Init(void) {
	DDRD |= (1 << DDD4);
	DDRD |= (1 << DDD5);
	DDRD |= (1 << DDD6);
	DDRD |= (1 << DDD7);
	
	DDRC |= (1 << DDC3);
	DDRC |= (1 << DDC4);
	DDRC |= (1 << DDC5);
	
	DISABLE_DISPLAYS;
}

/* 
*	Calculates place values for the number input along with decimal places. Makes use of 
*	UART functions made previously to extract digits of a float value.
*/
void Disp_Set(float val)
{
	uint16_t hundreds, tens, ones, tenths, hundredths = 0;

	extract_digits(val, &ones, &tens, &hundreds);
	extractTenths(val, &tenths);
	extractHundredths(val, &hundredths);
	
	placeValues[0] = tens;
	placeValues[1] = ones;
	placeValues[2] = tenths;
	placeValues[3] = hundredths;
}
	
/* Turning a particular position on and off */
/* ds1 = 1; ds2 = 2; ds3 = 3; ds4 = 4 */

void position_on(uint8_t position)
{
	switch(position){
		case 1:
			PORTD &= ~displays[position-1];
			break;
		case 2:
			PORTD &= ~displays[position-1];
			break;
		case 3:
			PORTD &= ~displays[position-1];
			break;
		case 4:
			PORTD &= ~displays[position-1];
			break;
	}
}

/* Returns the seven segment binary pattern of a digit */
int8_t digit_to_sevenseg(int8_t number){
	switch(number){
		case 0:
			return sevenSegMapping[0];
		case 1:
			return sevenSegMapping[1];
		case 2:
			return sevenSegMapping[2];
		case 3:
			return sevenSegMapping[3];
		case 4:
			return sevenSegMapping[4];
		case 5:
			return sevenSegMapping[5];
		case 6:
			return sevenSegMapping[6];
		case 7:
			return sevenSegMapping[7];
		case 8:
			return sevenSegMapping[8];
		case 9:
			return sevenSegMapping[9];
	}
	return 0;
}

/* Functions for displaying a specific type of value */
/* Each function have a fixed DP point */

void set_voltage_display()
{
	disp_pos = 4;
	
	Disp_Set(rms_voltage);
	
	for(uint8_t i = 0; i < PLACE_VALUE_SIZE; i++){
		placeValues[i] = digit_to_sevenseg(placeValues[i]);
	}
	
	placeValues[1] DP_APPEND; /* Dp at ds2 */
	
	unit = 0; /* v */
}

void set_current_display()
{
	disp_pos = 4;
	
	Disp_Set(pk_current);
	
	/* Need to shift all values left to work with disp_scan_next() */
	for(uint8_t i = 0; i < PLACE_VALUE_SIZE-1; i++){
		placeValues[i] = digit_to_sevenseg(placeValues[i+1]);
	}
	
	placeValues[0] DP_APPEND; /* Dp at ds1 */
	
	unit = 1; /* A */
}

void set_power_display()
{
	disp_pos = 4;
	
	Disp_Set(power);
	
	/* Need to shift all values left to work with disp_scan_next() */
	for(uint8_t i = 0; i < PLACE_VALUE_SIZE-1; i++){
		placeValues[i] = digit_to_sevenseg(placeValues[i+1]);
	}
	
	placeValues[0] DP_APPEND; /* Dp at ds1 */
	
	unit = 2; /* P */
}

void set_energy_display()
{
	/* Tracks energy consumed from start up. Ignore the first value. */
	// static float energy_track = 0;
	
	disp_pos = 4;
	
	/*
	if(energy_track >= 9.99){
		energy_track = 0;
	}
	*/
	
	//Disp_Set(energy_track += energy);
	
	Disp_Set(energy);
	
	/* Need to shift all values left to work with disp_scan_next() */
	for(uint8_t i = 0; i < PLACE_VALUE_SIZE-1; i++){
		placeValues[i] = digit_to_sevenseg(placeValues[i+1]);
	}
	
	placeValues[0] DP_APPEND; /* Dp at ds1 */
	
	unit = 3; /* E */
}

/* Send the next digit to Disp_Send() and position_on() */
void disp_scan_next()
{
	switch(disp_pos){
		case 1:
			Disp_Send(placeValues[0]);
			break;
		case 2:
			Disp_Send(placeValues[1]);
			break;
		case 3:
			Disp_Send(placeValues[2]);
			break;
		case 4:
			Disp_Send(indicationUnit[unit]);
			break;
	}
	
	position_on(disp_pos);
	
	if(disp_pos == 1){
		disp_pos = 4;
	} else {
		disp_pos--;
	}
}

/* Sets the display of next value */
void disp_next_value()
{
	static uint8_t to_disp = 0;
	
	change_display = 0;
		
	if(to_disp >= 3){
		to_disp = 0;
	} else {
		to_disp++;
	}
	
	switch(to_disp){
		case 0:
			set_voltage_display();
			break;
		case 1:
			set_current_display();
			break;
		case 2:
			set_power_display();
			break;
		case 3:
			set_energy_display();
			break;
	}
}