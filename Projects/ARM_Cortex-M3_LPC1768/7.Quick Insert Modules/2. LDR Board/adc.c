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
#include "gpio.h"

void adc_int(int ADC_PIN)
{
	uint32_t  clock, DataReg, ADC_Data, a;
	uint8_t channelNum;	
	SystemInit();
	channelNum = 0;
  
	LPC_SC->PCONP |= (1<<12);
	LPC_ADC->ADCR = ((1<<ADCR_PDN) | (10<<ADCR_CLKDIV));
	LPC_PINCON->PINSEL1|= 0x01<<ADC_PIN;
	clock = SystemCoreClock/4;
	LPC_ADC->ADCR |= (1 << ADCR_SEL0);																													
	LPC_ADC->ADCR |= ((clock/1000000 - 1)	<< ADCR_CLKDIV);																				
	LPC_ADC->ADCR |= ((0 << ADCR_BURST) | (1 << ADCR_PDN) | (0 << ADCR_START) | (0 << ADCR_EDGE));
	
	GPIO_SetPinDir(PIN0_16,OUTPUT);
	GPIO_SetPinDir(PIN0_17,OUTPUT);
	
	while(1)
	{
		LPC_ADC->ADCR &= 0xFFFFFF00;
		LPC_ADC->ADCR |= (1 << ADCR_START) | (1 << ADCR_SEL0);		
		do
		{
			DataReg = *(volatile unsigned long *)(LPC_ADC_BASE + ADC_OFFSET + ADC_RESULT* channelNum);
		}
		while(!(DataReg & ADC_DONE));									   
		LPC_ADC->ADCR &= 0xF8FFFFFF;															
		ADC_Data = (DataReg>>ADC_RESULT)&0xFFF;	
		UART0_WriteString("\n\rADC0: ");
		a = ADC_Data/4;
		if(a>150)
		{
			GPIO_PinWrite(PIN0_16,LOW);
			GPIO_PinWrite(PIN0_17,HIGH);
		}
		else
		{
			GPIO_PinWrite(PIN0_16,HIGH);
			GPIO_PinWrite(PIN0_17,LOW);
		}
		split(a);
	 }
}
