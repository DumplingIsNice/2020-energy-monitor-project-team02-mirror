#define DSP_C /* for inclusion of "dsp.h" */

#include "common.h"
#include "dsp.h"
#include "adc.h"
#include "timer0.h"

#include <string.h>
#include <math.h>
#include <avr/interrupt.h>

#define PI 3.141592
#define CUBE(x) (x * x * x)
#define SQUARE(x) (x * x)

volatile unsigned currently_sampling = 0;

/* Inital channel is voltage (we sample voltage first, then current)
 * (Note the ZC interrupt will start with the opposit of the current channel)
 */
int current_adc_channel = ADC_CH_CURRENT;

/* Raw Voltage and Current Readings (Along with time value of each reading) */
volatile unsigned adc_voltages[RAW_ARRAY_SIZE];
volatile unsigned adc_voltages_head; /* index to next free space in array */

volatile unsigned adc_currents[RAW_ARRAY_SIZE];
volatile unsigned adc_currents_head;  /* index to next free space in array */

/* Reverse Gained array of values */
float raw_voltages[RAW_ARRAY_SIZE];
float raw_currents[RAW_ARRAY_SIZE];

float interpolated_voltages[INTERPOLATED_ARRAY_SIZE];
float interpolated_currents[INTERPOLATED_ARRAY_SIZE];

/* Array of (interpolated) V * (interpoloated) I */
float instantanous_power[INTERPOLATED_ARRAY_SIZE];

float power;
float rms_voltage;
float pk_current;
float energy;

/* Zero Crossing Interrupt */
/* Currently sampling one cycle of the waveform at a time */
static volatile int16_t elapsed_cycle_time = 0;

/* Using Simpson's Rule */
static float numerical_intergreat(float *input)
{
	float numericalResult = input[0];

	for(uint8_t i = 1; i < 37 ; i= i+2){
		numericalResult = numericalResult + input[i] * 4;
		numericalResult = numericalResult + input[i + 1] * 2;
	}

	numericalResult = numericalResult + input[37] * 4;
	numericalResult = numericalResult + input[38];
	numericalResult = numericalResult * (0.0005 / 3);

	return numericalResult;
}

/* Cubic interpolate between a two points */
static float cubic_point(float x, float y0, float y1, float y2, float y3)
{
	float a = (-1.f / 2 * y0) + (3.f / 2 * y1) - (3.f / 2 * y2) + (1.f / 2 * y3);
	float b = y0 - (5.f / 2 * y1) + (2.f * y2) - (1.f / 2 * y3);
	float c = (-1.f / 2 * y0) + (1.f / 2 * y2);
	float d = y1;
		
	return (a * CUBE(x)) + (b * SQUARE(x)) + (c * x) + (d);
}

/* Cubic interpolate the raw arrays */
void cubic_interpolate()
{
	unsigned i, j;

	/* Voltage */
	/* First point is the same */
	i = j = 0;
	/* First point is the same */
	interpolated_voltages[j++] = raw_voltages[i];
	/* Point between first and second point is calculated a little differently (most inaccurate) */
	interpolated_voltages[j++] = cubic_point(0.5, 2 * raw_voltages[i] - raw_voltages[i + 1], raw_voltages[i], raw_voltages[i + 1], raw_voltages[i + 2]);
	for (++i; i < 20 - 2; ++i) {
		/* Original Point (y0) */
		interpolated_voltages[j++] = raw_voltages[i];
		/* Create new (Missing) Mid-Point */
		interpolated_voltages[j++] = cubic_point(0.5, raw_voltages[i - 1], raw_voltages[i], raw_voltages[i + 1], raw_voltages[i + 2]);
	}
	/* Point between second-to-last and last point is calculated a little differently (most inaccurate) */
	interpolated_voltages[j++] = raw_voltages[i];
	interpolated_voltages[j++] = cubic_point(0.5, raw_voltages[i - 1], raw_voltages[i], raw_voltages[i + 1], 2 * raw_voltages[i + 1] - raw_voltages[i]);
	interpolated_voltages[j++] = raw_voltages[++i];

	/* Current */
	i = j = 0;
	/* First point is the same */
	interpolated_currents[j++] = raw_currents[i];
	/* Point between first and second point is calculated a little differently (most inaccurate) */
	interpolated_currents[j++] = cubic_point(0.5, 2 * raw_currents[i] - raw_currents[i + 1], raw_currents[i], raw_currents[i + 1], raw_currents[i + 2]);
	for (++i; i < 20 - 2; ++i) {
		/* Original Point (y0) */
		interpolated_currents[j++] = raw_currents[i];
		/* Create new (Missing) Mid-Point */
		interpolated_currents[j++] = cubic_point(0.5, raw_currents[i - 1], raw_currents[i], raw_currents[i + 1], raw_currents[i + 2]);
	}
	/* Point between second-to-last and last point is calculated a little differently (most inaccurate) */
	interpolated_currents[j++] = raw_currents[i];
	interpolated_currents[j++] = cubic_point(0.5, raw_currents[i - 1], raw_currents[i], raw_currents[i + 1], 2 * raw_currents[i + 1] - raw_currents[i]);
	interpolated_currents[j++] = raw_currents[++i];
}

void calculate_power()
{
	unsigned i;

	for (i = 0; i < INTERPOLATED_ARRAY_SIZE; ++i)
		instantanous_power[i] = interpolated_voltages[i] * interpolated_currents[i];

	power = numerical_intergreat(instantanous_power) / (period_ms * 1e-3);
}

/* NOTE: This funciton must be called after calculating power !! */
void calculate_energy()
{
	energy += power * (period_ms * 1e-3);
}

/* NOTE the RMS Voltage calculation should be done last as it overrides the
 * interpolated_voltages array with the square of the interpolated voltages
 */
void calculate_rms_voltage()
{
	unsigned i;

	/* WARNING: interpolated_voltages IS NOW SQUARED !!! */
	for (i = 0; i < INTERPOLATED_ARRAY_SIZE; ++i) {
		interpolated_voltages[i] = SQUARE(interpolated_voltages[i]);
	}

	rms_voltage = sqrt(numerical_intergreat(interpolated_voltages) / (period_ms * 1e-3));

}

void calculate_pk_current()
{
	unsigned i;
	for (pk_current = i = 0; i < INTERPOLATED_ARRAY_SIZE; ++i)
		if (interpolated_currents[i] > pk_current)
			pk_current = interpolated_currents[i];
}


/* Convert ADC Value (0 - 1023) to Real Analogue Sensor Voltage Value */
void adc2real_voltage()
{
	int i;

	const float vOffset = 2.1;
	
	// Voltage divider inverse gain
	const uint16_t Rb1 = 3300;
	const uint16_t Ra1 = 56000;
	const float dividerGain = 1/ (float) (Rb1 / (float) (Ra1 + Rb1));
	
	
	// Voltage amplifier gain
	const uint16_t R2 = 4700;
	const uint16_t R1 = 4700;
	const float amplifierGain =  1 / (float) (R2 / ((float) R1));

	for (i = 0; i < RAW_ARRAY_SIZE; ++i) {
		/* The voltage values in raw_currents are actually the ADC values
		 * Overwrite them with the actual raw voltage values
		 */
		/* raw_voltages[i] = (float) 0.0877427 * raw_voltages[i] - (float) 37.7365; */
		raw_voltages[i] = ((5 * adc_voltages[i] / 1024.f) - vOffset) * dividerGain * amplifierGain;
	}
}

/* Convert ADC Value (0 - 1023) to Real Analogue Sensor Voltage Value */
void adc2real_current()
{
	int i;

	const float vOffset = 2.1;
	
	// Voltage divider inverse gain
	const float Rs1 = 0.56;
	const float dividerGain = 1 / (float) (Rs1);
	
	
	// Voltage amplifier gain
	const uint16_t R2 = 56000;
	const uint16_t R1 = 22000;
	const float amplifierGain =  1 / (float) (R2 / ((float) R1));
	
		
	
	for (i = 0; i < RAW_ARRAY_SIZE; ++i) {
		/* The voltage values in raw_currents are actually the ADC values
		 * Overwrite them with the actual raw voltage values
		 */
		/* raw_currents[i] = 0.0034253 * raw_currents[i] - 1.4731673; */
		raw_currents[i] = ((5 * adc_currents[i] / 1024.f) - vOffset) * dividerGain * amplifierGain;
	}
}

ISR(INT0_vect)
{
	extern volatile unsigned enable_zc;
	//Use this LED to check if interrupt is called.
	//TGL_PORT(PORTB, PORTB5);

	/* Zero crossing indicates the start or end of a cycle of sampling */
	if (!currently_sampling && enable_zc) {
		currently_sampling = 1;
		period_ms = adc_voltages_head = adc_currents_head = 0;
		/* Change the channel we will sample next */ 
		if (current_adc_channel == ADC_CH_VOLTAGE) {
			adc_set_channel(ADC_CH_CURRENT);
		} else {
			adc_set_channel(ADC_CH_VOLTAGE);
		}
		timer0_reset();
	} else if (currently_sampling && enable_zc) {
		currently_sampling = 0;
		enable_zc = 0;
		timer0_stop();
		/* Incriment it by one as the final timer interrupt won't occur */
		++period_ms;
		/* Force sample the ADC one more time to get 20 samples */
		SET_PORT(ADCSRA, ADSC);
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
