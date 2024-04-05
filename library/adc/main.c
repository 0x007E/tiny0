/* -----------------------------------------
* G.Raf^engineering
* www.sunriax.at (github.com/0x007e)
* -----------------------------------------
*    Platform: Independent
*    Hardware: ATTiny406/1606/...
* -----------------------------------------
*     Version: 1.0 Release
*      Author: G.Raf
* Description:
*	Sample for initializing A/D converter
* -----------------------------------------
*/

#define F_CPU 20000000UL

// System libraries
#include <avr/io.h>
#include <util/delay.h>

// User libraries
#include "adc.h"
#include "../system/system.h"

int main(void)
{
	// Define output port
	PORTC.DIRSET = PIN3_bm | PIN2_bm | PIN1_bm | PIN0_bm;
	
	// Initialize clock system
	system_init();
	
	// Initialize A/D converter
	// Resolution: 10 bit
	// Samplerate: 156.25ksps
	adc_init();
	
	// Select A/D channel 1 (PA1) -> 10k potentiometer
	adc_channel(ADC_CH1);
	
	while (1)
	{
		// Write converted value to PORTC
		// PORT only has 4 Bit so the lower bits are thrown away
		PORTC.OUT = (adc_read()>>6);
		
		// To build an average there are two possible solutions
		// Use 10 samples and build an average in software:
		PORTC.OUT = (adc_average(10)>>6);
		
		// Accumulate 8 samples in hardware:
		adc_accumulation(ADC_Sample_8);
		
		PORTC.OUT = (adc_read()>>6);
		
		adc_accumulation(ADC_Sample_None);
		
		_delay_ms(100);
	}
}