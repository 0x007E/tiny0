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
*	Sample for initializing twi bus
* -----------------------------------------
*/

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Hardware setup
//
//             +-----+
//             |  P  |
// +-----------+  D  +-------+                       AT24C02
// |     A     |  I  |       |                    +-----------+
// |     T     +-----+   +---+ +> VCC ---- VCC <+ |     E     |
// |     I               | P | |                | |     E     |
// |     N               | O |+++              +++|     P     |
// |     Y               | R || | 10k      10k | ||     R     |
// |     *               | T || |              | ||     O     |
// |     0               | B |+++              +++|     M     |
// |     6               |   | |                | |           |
// |                     |   | |-> PB1 -- SDA <-+ |           |
// |                     |   | +-> PB0 -- SCL <-- |           |
// |                     +---+  -> GND -- GND <-  |           |
// +~~~~~~~~~~~~~~~~~~~~~~~~~+                    +-----------+
//
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#define F_CPU 20000000UL

// EEPROM settings
#define SLAVE_ADDR   0x42   // TWI_Slave address of the EEPROM
#define EEPROM_ADDR  0xF0   // EEPROM memory address
#define EEPROM_DATA  0xF0   // EEPROM test data

// System libraries
#include <avr/io.h>
#include <util/delay.h>

// User libraries
#include "twi.h"
#include "../system/system.h"

int main(void)
{
	// Define input port
	PORTB.DIRCLR = PIN1_bm | PIN0_bm;

    // Enable pull-up on SCL and SDA if no external pull-ups are present.
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // !!!        INFORMATION           !!!
    // !!! If the pullup resistor on    !!!
    // !!! SCL/SDA has a very high      !!!
    // !!! resistance, it could be      !!!
    // !!! necessary to slow down the   !!!
    // !!! TWI clock speed or manually  !!!
    // !!! mount 10k resistors between  !!!
    // !!! SCL -> VCC and SDA -> VCC    !!!
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//PORTB.PIN0CTRL = PORT_PULLUPEN_bm;
	//PORTB.PIN1CTRL = PORT_PULLUPEN_bm;
	
	// Define output port
	PORTC.DIRSET = PIN0_bm;
	
	// Initialize clock system
	system_init();
	
	// Initialize TWI
	//  Mode: Master
	// Speed: 100kHz
	//
	// Details can be found in twi.c
	twi_init();
	
	// EEPROM WRITE routine
	twi_start();
	twi_address(SLAVE_ADDR, TWI_Write);
	twi_set(EEPROM_ADDR);
	twi_set(EEPROM_DATA);
	twi_stop();
	_delay_ms(5);
	
	while(1)
	{
    	unsigned char data;
    	
    	// EEPROM READ routine
    	twi_start();
    	twi_address(SLAVE_ADDR, TWI_Write);
    	twi_set(EEPROM_ADDR);
    	twi_start();
    	twi_address(SLAVE_ADDR, TWI_Read);
    	twi_get(&data, TWI_NACK);
    	twi_stop();
    	
    	// Check if data written to EEPROM is same as data that was received
    	if(EEPROM_DATA == data)
    	    PORTC.OUTSET = PIN0_bm;
	}
}