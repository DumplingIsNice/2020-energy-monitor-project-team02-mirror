#include "common.h"
#include "display.h"
#include "dsp.h"
#include "uart.h"

/* Common toggle defines for display and bit shift register */
#define disableDisplays PORTD |= (0b11110000)
#define enableDisplays PORTD |= (0b00000000)
#define shiftRegOn PORTC |= (1<<PORTC5) 
#define shiftRegOff PORTC &= ~(1<<PORTC5)

#define DP_APPEND |= (1<<7)
#define PLACE_VALUE_SIZE 4

/* Holds place value digits in an array, calculated using extract functions in UART */
static uint8_t placeValues[4] = {0,0,0,0};

/* Holds ports for each display (1 - 4 respectively) where displays[0] = Ds1, displays[1] = Ds2 etc */
static uint8_t displays[4] = {(1<<PORTD4), (1<<PORTD5), (1<<PORTD6), (1<<PORTD7)};
	
/* Tracks energy consumed from start up. Ignore the first value. */
static float energy_track = 0; 

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

static const uint8_t indicationUnit[4] = 
{
	0b00011100, /* v */
	0b01110111, /* A */
	0b01110011, /* P */
	0b01111001, /* E */
};

/* the seven segment number to render to the display */
static volatile uint8_t disp_num = 0;
/* the current position of the 4-digit number we're displaying */
static volatile uint8_t disp_pos = 4;

static volatile uint8_t unit = 0;

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
	
	//3. Disable all digits
	disableDisplays;
	//4. Latch the output by toggling SH_ST pin
	toggle_SH_ST();
	//5. Now, depending on the value of pos, enable the correct digit
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

/* Display initialise */
void Disp_Init(void) {
	DDRD |= (1 << DDD4);
	DDRD |= (1 << DDD5);
	DDRD |= (1 << DDD6);
	DDRD |= (1 << DDD7);
	
	DDRC |= (1 << DDC3);
	DDRC |= (1 << DDC4);
	DDRC |= (1 << DDC5);
	
	disableDisplays;
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
	disableDisplays;
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

void display_power(float power)
{
	
	/*
	uint8_t to_send = 0;
	uint8_t i = 1;
	
	Disp_Set(power); // Sets the current placeValue, containing the digits of power.
	
	while(1){
		to_send = digit_to_sevenseg(placeValues[i]);
		
		Disp_Send(to_send);
		position_on(i);
		
		if(i >= 4){
			i = 1;
		} else {
			i++;	
		}
	} */
}

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

void disp_next_value()
{
	
}

void disp_reset()
{
	disp_pos = 4;
}