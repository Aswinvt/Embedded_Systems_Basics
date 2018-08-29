/*
 * File name            : main.c
 * Compiler             : MDK-Lite
 * IDE                  : Keil uVision V5
 * Author               : Etiq Technologies
 * Processor            : LPC1768
 * Created on           : November 20, 2017, 01:20 PM
 * Description          : Program for ADC data convertion for UART and LCD
 */
 
#include "uart.h"

void split(unsigned char s)
{
	unsigned char a[4];
	int x=0;

	while(x<4){
		a[x] = s%10;
		s = s/10;
		x++;
	}
	
	do
	{
		--x;
		UART0_WriteChar(a[x]+48);
	}while(x);
}
