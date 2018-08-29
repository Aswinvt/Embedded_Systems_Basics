/*
 * File name            : main.c
 * Compiler             : MDK-Lite
 * IDE                  : Keil uVision V5
 * Author               : Etiq Technologies
 * Processor            : LPC1768
 * Created on           : November 20, 2017, 01:15 PM
 * Description          : Program for IR Addon board interface
 */
 
#include "interrupt.h"

void EINT0_IRQHandler (void) 
{
	int LED = 0;	
	LPC_SC->EXTINT |= (1<<EXTINT0);
	GPIO_PinWrite(PIN0_16, LOW);
	DELAY_ms(500);
	GPIO_PinWrite(PIN0_16, HIGH);
	DELAY_ms(500);
	LED++;
}

int main()
{
	SystemInit();
	LPC_PINCON->PINSEL4 &= (EINT_CLR << EINT_0);
	LPC_PINCON->PINSEL4 |= (EINT_FUNC << EINT_0);
	
	LPC_SC->EXTMODE |= EDGE_SENSE;
	LPC_SC->EXTPOLAR|= POL_LOWFALL;
	
	NVIC_EnableIRQ(EINT0_IRQn);

	GPIO_SetPinDir(PIN0_16, OUTPUT);
	
	while(1)
	{
		GPIO_PinWrite(PIN0_16, HIGH);
	}
}
