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
 *	Sample for initializing system clock
 * -----------------------------------------
 */ 

#define F_CPU 20000000UL

// System libraries
#include <avr/io.h>
#include <util/delay.h>

// User libraries
#include "system.h"

int main(void)
{
	// Define signal port
	PORTA.DIR = PIN1_bm;
	
	// Initialize clock system
	system_init();
	
	while (1)
	{
		PORTA.OUTTGL = PIN1_bm;
		_delay_ms(1000);
	}
}