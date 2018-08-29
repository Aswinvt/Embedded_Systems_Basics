/*
 * File name            : main.c
 * Compiler             : MDK-Lite
 * IDE                  : Keil uVision V5
 * Author               : Etiq Technologies
 * Processor            : LPC1768
 * Created on           : November 20, 2017, 01:30 PM
 * Description          : Program for LDR Addon board interface
 */
 
#include "adc.h"

int main()
{
	uart_int(9600);									//Initializing UART with baud rate 9600
	adc_int(AD0_0);									//Initializing ADC for LDR input
	return 0;
}
