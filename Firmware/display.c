#include "common.h"

static const unsigned char sevenSegMapping[] = {
	0x3F, /* 0 */
	0x06, /* 1 */
	0x5B, /* 2 */
	0x4F, /* 3 */
	0x66, /* 4 */
	0x6D, /* 5 */
	0x7D, /* 6 */
	0x07, /* 7 */
	0x7F, /* 8 */
	0x6F, /* 9 */
	0x80  /* . (decimal point) */
};


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
