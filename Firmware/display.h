#ifndef DISPLAY_H_
#define DISPLAY_H_

extern volatile uint8_t change_display; /* Defined in timer2.c */

/* Display initialisation */
void disp_init(void);

/* Sends an integer to display with number value input to the function */
void disp_send(uint8_t val);

/* Helper Functions: Control signal control */
void toggle_SH_ST();
void toggle_SH_CP();
void init_shift_reg();

/*
*	Calculates place values for the number input along with decimal places. Makes use of
*	UART functions made previously to extract digits of a float value.
*/
void disp_set(float val);

/* Turning a particular position on */
/* ds1 = 1; ds2 = 2; ds3 = 3; ds4 = 4 */
void position_on(uint8_t position);

/* Returns the seven segment binary pattern of a digit */
int8_t digit_to_sevenseg(int8_t number);

/* Functions for displaying a specific type of value */
/* Each function have a fixed DP point */

void set_voltage_display(); // Dp at ds2
void set_current_display(); // Dp at ds1
void set_power_display();	// Dp at ds1
void set_energy_display();	// Accumulative. Resets at certain value.

/* Send the next digit to Disp_Send() and display position */
void disp_scan_next();

/* Sets the display of next value */
void disp_next_value();

#endif