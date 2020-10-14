
// Sends an integer to display with number value input to the function
void Disp_Send(uint8_t val);

/* Display initialise */
void Disp_Init(void);

/*
*	Calculates place values for the number input along with decimal places. Makes use of
*	UART functions made previously to extract digits of a float value.
*/
void Disp_Set(float val);