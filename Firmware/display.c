#include "common.h"
#include "uart.h"


/* Common toggle defines for display and bit shift register */
#define disableDisplays PORTD |= (0b11110000)
#define enableDisplays PORTD |= (0b00000000)
#define shiftRegOn PORTC |= (1<<PORTC5) 
#define shiftRegOff PORTC &= ~(1<<PORTC5)

/* Holds place value digits in an array, calculated using extract functions in UART */
static uint8_t placeValues[4] = {0,0,0,0};

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

static const uint8_t indicationUnit[4] = 
{
	0b00011100, /* v */
	0b01110111, /* A */
	0b01110011, /* P */
	0b01111001, /* E */
};

/* Display initialise */
void Disp_Init(void) {
	DDRD |= (1 << DDD4);
	DDRD |= (1 << DDD5);
	DDRD |= (1 << DDD6);
	DDRD |= (1 << DDD7);
	
	DDRC |= (1 << DDC3);
	DDRC |= (1 << DDC4);
	DDRC |= (1 << DDC5);
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


void Disp_Send(uint8_t val) {
	/* SHIFT REGISTER WORKS ON RISING EDGE TRIGGER */
	/* To simulate rising edge on SH_CP, toggle high then low to transmist */

	/* Shift MSB first, ignoring decimal point, by setting SH_DS */
	PORTC = (PORTC & ~(1 << 4)) | ((val & (1 << 6))) >> 3;
	PORTC ^= (1 << 3);  /* Toggle SH_CP pin to transmit data */
	PORTC ^= (1 << 3);  /* Toggle SH_CP pin to stop transmiting */

	PORTC = (PORTC & ~(1 << 4)) | ((val & (1 << 6))) >> 2;
	PORTC ^= (1 << 3);  /* Toggle SH_CP pin to transmit data */
	PORTC ^= (1 << 3);  /* Toggle SH_CP pin to stop transmiting */

	PORTC = (PORTC & ~(1 << 4)) | ((val & (1 << 5))) >> 1;
	PORTC ^= (1 << 3);  /* Toggle SH_CP pin to transmit data */
	PORTC ^= (1 << 3);  /* Toggle SH_CP pin to stop transmiting */

	PORTC = (PORTC & ~(1 << 4)) | ((val & (1 << 4))) >> 0;
	PORTC ^= (1 << 3);  /* Toggle SH_CP pin to transmit data */
	PORTC ^= (1 << 3);  /* Toggle SH_CP pin to stop transmiting */

	PORTC = (PORTC & ~(1 << 4)) | ((val & (1 << 3))) << 1;
	PORTC ^= (1 << 3);  /* Toggle SH_CP pin to transmit data */
	PORTC ^= (1 << 3);  /* Toggle SH_CP pin to stop transmiting */

	PORTC = (PORTC & ~(1 << 4)) | ((val & (1 << 2))) << 2;
	PORTC ^= (1 << 3);  /* Toggle SH_CP pin to transmit data */
	PORTC ^= (1 << 3);  /* Toggle SH_CP pin to stop transmiting */

	PORTC = (PORTC & ~(1 << 4)) | ((val & (1 << 1))) << 3;
	PORTC ^= (1 << 3);  /* Toggle SH_CP pin to transmit data */
	PORTC ^= (1 << 3);  /* Toggle SH_CP pin to stop transmiting */

	/* LSB */
	PORTC = (PORTC & ~(1 << 4)) | ((val & (1 << 0))) << 4;
	PORTC ^= (1 << 3);  /* Toggle SH_CP pin to transmit data */
	PORTC ^= (1 << 3);  /* Toggle SH_CP pin to stop transmiting */

	/* Now set SH_ST to latch the output of the shift register */
	PORTC |= (1 << 5);
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