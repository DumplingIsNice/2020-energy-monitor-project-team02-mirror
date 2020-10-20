#ifndef DISPLAY_H_
#define DISPLAY_H_

// Sends an integer to display with number value input to the function
void Disp_Send(uint8_t val);

/* control signal control */

void toggle_SH_ST();
void toggle_SH_CP();
void init_shift_reg();

/* Display initialise */
void Disp_Init(void);

/*
*	Calculates place values for the number input along with decimal places. Makes use of
*	UART functions made previously to extract digits of a float value.
*/
void Disp_Set(float val);

/* Function for displaying a specific type for value */
/* Each function have a fixed DP point */

void set_voltage_display(); // Dp at ds2

void display_current(); // Dp at ds1

void display_power(float power); // Dp at ds1

void display_energy(); // This one require a persistant variable. Resets at certain value.

/* Turning a particular position on and off */
/* ds1 = 1; ds2 = 2; ds3 = 3; ds4 = 4 */

void position_on(uint8_t position);

/* Returns the seven segment binary pattern of a digit */

int8_t digit_to_sevenseg(int8_t number);

/* Send the next digit to Disp_Send() and display position */
void disp_scan_next();

/* Sets flag to display next value in rotation */
void disp_next_value();

/* resets display parameters for next value */
void disp_reset();

#endif