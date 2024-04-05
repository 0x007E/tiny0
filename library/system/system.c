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
 *	Library for initializing system clock
 * -----------------------------------------
 */

#include "system.h"

void system_init(void)
{
    CCP = CCP_IOREG_gc;
    CLKCTRL.MCLKCTRLA = SYSTEM_CLOCK;
    while(!(CLKCTRL.MCLKSTATUS & SYSTEM_CLOCK_BIT))
	{
		;
	}
    
    #ifdef SYSTEM_PER_CLOCK_PRESCALER
        CCP = CCP_IOREG_gc;
        CLKCTRL.MCLKCTRLB = SYSTEM_PER_CLOCK_PRESCALER | CLKCTRL_PEN_bm;
    #endif
    
    #if SYSTEM_CLOCK == CLKCTRL_CLKSEL_OSC20M_gc
        CCP = CCP_IOREG_gc;
        CLKCTRL.OSC20MCTRLA = CLKCTRL_RUNSTDBY_bm;  
    #endif
}