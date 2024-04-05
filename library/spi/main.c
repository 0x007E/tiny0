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
*	Sample for initializing spi bus
* -----------------------------------------
*/

#define F_CPU 20000000UL

// System libraries
#include <avr/io.h>
#include <util/delay.h>

// User libraries
#include "spi.h"
#include "../system/system.h"

int main(void)
{
	// Define input port
	PORTB.DIRCLR = PIN3_bm | PIN2_bm | PIN1_bm | PIN0_bm;
	PORTB.PIN0CTRL = PORT_PULLUPEN_bm;
	PORTB.PIN1CTRL = PORT_PULLUPEN_bm;
	PORTB.PIN2CTRL = PORT_PULLUPEN_bm;
	PORTB.PIN3CTRL = PORT_PULLUPEN_bm;
	
	// Define output port
	PORTC.DIRSET = PIN3_bm | PIN2_bm | PIN1_bm | PIN0_bm;
	
	// Initialize clock system
	system_init();
	
	// SPI Initialization
	//      Mode: Master
	// Direction: MSB
	//  Transfer: SPI_Rising/SPI_Rising
	//
	// Details can be found in spi.c
	spi_init(SPI_MSB, SPI_Rising, SPI_Rising);
	
	while (1)
	{
		// Use a simple loopback mode (connect MOSI to MISO)
		// to check the function of the SPI bus. There are 4 Switches
		// connected to PORTB (3:0). If one or more switches are
		// pressed the status LEDs on PORTC should remain the status
		// of the switches. If the connection between MOSI and MISO
		// is removed the status LEDs should all be HIGH (active)
		// because of the activated pull-up on MISO!!!
		PORTC.OUT = spi_transfer(~(0x0F & PORTB.IN));
		_delay_ms(1000);
	}
}