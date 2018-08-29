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
	uint32_t  clock, DataReg, ADC_Data;
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
	GPIO_SetPinDir(PIN0_18,OUTPUT);
	GPIO_SetPinDir(PIN0_19,OUTPUT);
	GPIO_SetPinDir(PIN0_20,OUTPUT);
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
		ADC_Data = ((DataReg>>ADC_RESULT)&0xFFF);
		DELAY_ms(100);
		split(ADC_Data/2);
		if(ADC_Data/2<155&&ADC_Data/2>0)
		{
			GPIO_PinWrite(PIN0_16,HIGH);
			DELAY_ms(50);
			GPIO_PinWrite(PIN0_17,LOW);
			GPIO_PinWrite(PIN0_18,LOW);
			GPIO_PinWrite(PIN0_19,LOW);
			GPIO_PinWrite(PIN0_20,LOW);
		}
		if(ADC_Data/2<175&&ADC_Data/2>155)
		{
			GPIO_PinWrite(PIN0_17,HIGH);
			DELAY_ms(50);
			GPIO_PinWrite(PIN0_16,LOW);
			GPIO_PinWrite(PIN0_18,LOW);
			GPIO_PinWrite(PIN0_19,LOW);
			GPIO_PinWrite(PIN0_20,LOW);
		}
		if(ADC_Data/2<195&&ADC_Data/2>175)
		{
			GPIO_PinWrite(PIN0_18,HIGH);
			DELAY_ms(50);
			GPIO_PinWrite(PIN0_16,LOW);
			GPIO_PinWrite(PIN0_17,LOW);
			GPIO_PinWrite(PIN0_19,LOW);
			GPIO_PinWrite(PIN0_20,LOW);
		}
		if(ADC_Data/2<215&&ADC_Data/2>195)
		{
			GPIO_PinWrite(PIN0_19,HIGH);
			DELAY_ms(50);
			GPIO_PinWrite(PIN0_16,LOW);
			GPIO_PinWrite(PIN0_17,LOW);
			GPIO_PinWrite(PIN0_18,LOW);
			GPIO_PinWrite(PIN0_20,LOW);
		}
		if(ADC_Data/2<255&&ADC_Data/2>215)
		{
			GPIO_PinWrite(PIN0_20,HIGH);
			DELAY_ms(50);
			GPIO_PinWrite(PIN0_16,LOW);
			GPIO_PinWrite(PIN0_17,LOW);
			GPIO_PinWrite(PIN0_18,LOW);
			GPIO_PinWrite(PIN0_19,LOW);
		}
	 }
}
