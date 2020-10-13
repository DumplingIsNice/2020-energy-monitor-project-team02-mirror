#define DSP_C /* for inclusion of "dsp.h" */

#include "common.h"
#include "dsp.h"
#include "adc.h"
#include "timer0.h"

#include <string.h>
#include <avr/interrupt.h>

#define CUBE(x) (x * x * x)
#define SQUARE(x) (x * x)

volatile unsigned char complete_sampling = 1; /* So that it resets on the first ZC interrupt  */

/* Inital channel is voltage (we sample voltage first, then current) */
int current_adc_channel = ADC_CH_VOLTAGE;

/* Raw Voltage and Current Readings (Along with time value of each reading) */
volatile unsigned adc_voltages[RAW_ARRAY_SIZE];
volatile unsigned adc_voltages_t[RAW_ARRAY_SIZE];
volatile unsigned adc_voltages_head; /* index to next free space in array */

volatile unsigned adc_currents[RAW_ARRAY_SIZE];
volatile unsigned adc_currents_t[RAW_ARRAY_SIZE];
volatile unsigned adc_currents_head;  /* index to next free space in array */

/* Reverse Gained array of values */
volatile float raw_voltages[RAW_ARRAY_SIZE];
volatile float raw_voltages_t[RAW_ARRAY_SIZE];

volatile float raw_currents[RAW_ARRAY_SIZE];
volatile float raw_currents_t[RAW_ARRAY_SIZE];

/* Zero Crossing Interrupt */
/* Currently sampling one cycle of the waveform at a time */
static volatile int16_t elapsed_cycle_time = 0;

/* Cubic interpolate between a two points */
float cubic_point(float t, float yleft, float y0, float y1, float yright)
{
	float a = (-1 / 2 * yleft) + (3 / 2 * y0) - (3 / 2 * y1) + (1 / 2 * yright);
	float b = yleft - (5 / 2 * y0) + (2 * y1) - (1 / 2 * yright);
	float c = (-1 / 2 * yleft) + (1 / 2 * y1);
	float d = y0;

	return (a * CUBE(t)) + (b * SQUARE(t)) + (c * t) + (d);
}

/* Cubic interpolate the raw arrays */
void cubic_interpolate()
{
	/* !! TODO !! */
}

/* Convert ADC Value (0 - 1023) to Real Analogue Sensor Voltage Value */
void adc2real_voltage()
{
	int i;
	for (i = 0; i < RAW_ARRAY_SIZE; ++i) {
		/* The voltage values in raw_currents are actually the ADC values
		 * Overwrite them with the actual raw voltage values
		 */
		raw_voltages[i] = 0.087743 * raw_voltages[i] - 37.73636;
	}
}

/* Convert ADC Value (0 - 1023) to Real Analogue Sensor Voltage Value */
void adc2real_current()
{
	int i;
	for (i = 0; i < RAW_ARRAY_SIZE; ++i) {
		/* The voltage values in raw_currents are actually the ADC values
		 * Overwrite them with the actual raw voltage values
		 */
		raw_currents[i] = 0.003425 * raw_currents[i] - 1.47322;
	}
}

#if 0
/* Remove the gain and shifts added by all the analogue circuitry to get
 * back the original sensor voltage value
 */
void reverse_voltage_gain()
{
	int i;
	float vOffset = 2.1;

	// Voltage divider inverse gain
	uint16_t Rb1 = 3300;
	uint16_t Ra1 = 56000;
	float dividerGain = 1/(float)(Rb1/(float)(Ra1 + Rb1));


	// Voltage amplifier gain
	uint16_t R2 = 4700;
	uint16_t R1 = 4700;
	float amplifierGain =  1/(float)(R2/((float)R1));

	//float reversedVoltage = (dividerGain * amplifierGain * adc_voltage) - vOffset;
	for (i = 0; i < RAW_ARRAY_SIZE; ++i) {
		/* The voltage values in raw_currents are actually the ADC values
		 * Overwrite them with the actual raw voltage values
		 */
		raw_voltages[i] = (raw_voltages[i] - vOffset) * dividerGain * amplifierGain;
	}
}

/* Remove the gain and shifts added by all the analogue circuitry to get
 * back the original sensor current value
 */
void reverse_current_gain()
{
	int i;
	float vOffset = 2.1;
	
	
	// Voltage divider inverse gain
	float Rs1 = 0.56;
	float dividerGain = 1/(float)(Rs1);
	
	
	// Voltage amplifier gain
	uint16_t R2 = 56000;
	uint16_t R1 = 22000;
	float amplifierGain =  1/(float)(R2/((float)R1));
	
	for (i = 0; i < RAW_ARRAY_SIZE; ++i) {
		/* The current values in raw_currents are actually the ADC values
		 * Overwrite them with the actual raw current values
		 */
		raw_currents[i] = (raw_currents[i] - vOffset) * dividerGain * amplifierGain;
	}
}
#endif /* 0 */

ISR(INT0_vect)
{
	//Use this LED to check if interrupt is called.
	/*TGL_PORT(PORTB, PORTB5);*/

	/* Zero crossing indicates the start or end of a cycle of sampling */
	if (!complete_sampling) {
		timer0_stop();
		set_elapsed_cycle();

		/* Copy array values so it's not overwritten during calculation */

		raw_voltages[0] = adc_voltages[0];
		raw_voltages[1] = adc_voltages[1];
		raw_voltages[2] = adc_voltages[2];
		raw_voltages[3] = adc_voltages[3];
		raw_voltages[4] = adc_voltages[4];
		raw_voltages[5] = adc_voltages[5];
		raw_voltages[6] = adc_voltages[6];
		raw_voltages[7] = adc_voltages[7];
		raw_voltages[8] = adc_voltages[8];
		raw_voltages[9] = adc_voltages[9];

		raw_voltages_t[0] = adc_voltages_t[0];
		raw_voltages_t[1] = adc_voltages_t[1];
		raw_voltages_t[2] = adc_voltages_t[2];
		raw_voltages_t[3] = adc_voltages_t[3];
		raw_voltages_t[4] = adc_voltages_t[4];
		raw_voltages_t[5] = adc_voltages_t[5];
		raw_voltages_t[6] = adc_voltages_t[6];
		raw_voltages_t[7] = adc_voltages_t[7];
		raw_voltages_t[8] = adc_voltages_t[8];
		raw_voltages_t[9] = adc_voltages_t[9];

		raw_currents[0] = adc_currents[0];
		raw_currents[1] = adc_currents[1];
		raw_currents[2] = adc_currents[2];
		raw_currents[3] = adc_currents[3];
		raw_currents[4] = adc_currents[4];
		raw_currents[5] = adc_currents[5];
		raw_currents[6] = adc_currents[6];
		raw_currents[7] = adc_currents[7];
		raw_currents[8] = adc_currents[8];
		raw_currents[9] = adc_currents[9];

		raw_currents_t[0] = adc_currents_t[0];
		raw_currents_t[1] = adc_currents_t[1];
		raw_currents_t[2] = adc_currents_t[2];
		raw_currents_t[3] = adc_currents_t[3];
		raw_currents_t[4] = adc_currents_t[4];
		raw_currents_t[5] = adc_currents_t[5];
		raw_currents_t[6] = adc_currents_t[6];
		raw_currents_t[7] = adc_currents_t[7];
		raw_currents_t[8] = adc_currents_t[8];
		raw_currents_t[9] = adc_currents_t[9];

		complete_sampling = 1;
	} else {
		complete_sampling = 0;
		adc_set_channel(ADC_CH_VOLTAGE); /* Implicitly assumes voltage is first sample */
		adc_voltages_head = adc_currents_head = 0;
		timer0_reset();
	}
}

/* Initializes voltage zero crossing interrupt */
void voltage_zc_interrupt_init()
{
	SET_PORT(EIMSK, INT0);

	/* Rising edge trigger */
	SET_PORT(EICRA, ISC01), SET_PORT(EICRA, ISC00);
	
	/* Changing Edge trigger 
	EICRA |= (1 << ISC00); 
	EICRA &= ~(1 << ISC01); */
}

void set_elapsed_cycle()
{
	elapsed_cycle_time = miliseconds;
}

/* Returns the calculated period of current sample */
uint16_t get_period()
{
	return elapsed_cycle_time / CYCLE_SAMPLED;
}

/* Checks if the required cycles have elapsed */
void check_cycle_complete()
{
/*
	static int cycles = 0;
	
	if (cycles >= CYCLE_SAMPLED - 1){
		signal_start = false;
		cycles = 0;
	} else if (cycles < CYCLE_SAMPLED - 1){
		signal_start = true;
		cycles++;
	}
*/
}
