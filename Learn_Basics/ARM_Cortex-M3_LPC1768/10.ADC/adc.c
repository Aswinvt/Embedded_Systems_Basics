/*
 * File name            : main.c
 * Compiler             : MDK-Lite
 * IDE                  : Keil uVision V5
 * Author               : Etiq Technologies
 * Processor            : LPC1768
 * Created on           : November 20, 2017, 01:20 PM
 * Description          : Program for ADC
 */
 
#include "adc.h"

void adc_int(int ADC_PIN)
{
	uint32_t  clock, DataReg, ADC_Data;
	uint8_t channelNum;	
	SystemInit();
	channelNum = 0;
  
	LPC_SC->PCONP |= (1<<12);	// Power up the ADC module
	LPC_ADC->ADCR = ((1<<ADCR_PDN) | (10<<ADCR_CLKDIV)); // Funtions as ADC (0-3) pins when 01 is selected resp. under PINSEL1 reg. P0.23 (15,14), P0.24 (17,16), P0.25 (19,18), P0.26 (21,20)
	LPC_PINCON->PINSEL1|= 0x01<<ADC_PIN; // We will be using AD0 channel only.
	clock = SystemCoreClock/4;
	LPC_ADC->ADCR |= (1 << ADCR_SEL0);	// Select channel 0 on ADC0																												
	LPC_ADC->ADCR |= ((clock/1000000 - 1)	<< ADCR_CLKDIV);		// CLKDIV = (clock/ADC_CLOCK - 1)																		
	LPC_ADC->ADCR |= ((0 << ADCR_BURST) | (1 << ADCR_PDN) | (0 << ADCR_START) | (0 << ADCR_EDGE));
	
	while(1)
	{
		LPC_ADC->ADCR &= 0xFFFFFF00;
		LPC_ADC->ADCR |= (1 << ADCR_START) | (1 << ADCR_SEL0);		//Select AD0 channel and start the conversion process.
		do
		{
			DataReg = *(volatile unsigned long *)(LPC_ADC_BASE + ADC_OFFSET + ADC_RESULT* channelNum);
		}while(!(DataReg & ADC_DONE));					// When ADC_DONE is 1, the conversion is complete.				   
		LPC_ADC->ADCR &= 0xF8FFFFFF;															//Stop AD0 conversion process.
		ADC_Data = (DataReg>>ADC_RESULT)&0xFFF;	// The max value for the result will be in the range Vrefp (0xfff) and Vrefn (0x000)
		UART0_WriteString("\n\rADC0: ");
		split(ADC_Data);
	 }
}
