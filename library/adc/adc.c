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
 *	Library for initializing A/D converter
 * -----------------------------------------
 */

#include "adc.h"

void adc_init(void)
{
    ADC0.CTRLC = (ADC_CAPACITANCE<<ADC_SAMPCAP_bp) | ADC_REFERENCE | ADC_PRESCALER;
    ADC0.CTRLD = ADC_SAMPLE_DELAY_VARIATION | ADC_INITDLY_DLY0_gc | (ADC_SAMPLE_DELAY<<ADC_SAMPDLY_gp);
    ADC0.SAMPCTRL = ADC_SAMPLE_LENGTH;
    ADC0.CTRLA = ADC_RESOLUTION | ADC_ENABLE_bm;
    
    // Check if ADC interrupt handler is active
    #ifdef ADC_ADIE
        ADC0.INTCTRL = ADC_RESRDY_bm;   // Enable ADC interrupt
    #endif
}

void adc_disable(void)
{
    ADC0.CTRLA &= ~ADC_ENABLE_bm;
}

void adc_channel(ADC_Channel channel)
{
    ADC0.MUXPOS = ((0x1F & channel)<<ADC_MUXPOS_gp);   // Select ADC Channel
}

void adc_accumulation(ADC_Accumulation samples)
{
    ADC0.CTRLB = samples;
}

#ifndef ADC_ADIE

    unsigned int adc_read(void)
    {
        ADC0.COMMAND = ADC_STARTEI_bm;

        while(ADC0.COMMAND & ADC_STARTEI_bm)
        {
            ;
        }
        
        return ADC0.RES;
    }

    unsigned int adc_average(unsigned char samples)
    {
        unsigned long average = 0;
        
        for(unsigned char i=0; i < samples; i++)
        {
                average += adc_read();
        }
        
        average /= samples;
        
        return (unsigned int)(average);
    }
#endif