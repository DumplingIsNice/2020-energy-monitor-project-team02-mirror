#ifndef DISPLAY_H_
#define DISPLAY_H_

static float energy_track; // Tracks energy consumed from start up. Ignore the first value.

// Sends an integer to display with number value input to the function
void Disp_Send(uint8_t val);

/* Display initialise */
void Disp_Init(void);

/*
*	Calculates place values for the number input along with decimal places. Makes use of
*	UART functions made previously to extract digits of a float value.
*/
void Disp_Set(float val);

/* Function for displaying a specific type for value */
/* Each function have a fixed DP point */

void display_voltage(); // Dp at ds2

void display_current(); // Dp at ds1

void display_power(); // Dp at ds1

void display_energy(); // This one require a persistant variable. Resets at certain value.

/* Turning a particular position on and off */
/* ds1 = 1; ds2 = 2; ds3 = 3; ds4 = 4 */

void position_on(uint8_t position);

#endif