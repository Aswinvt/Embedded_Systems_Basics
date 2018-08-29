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

int main()
{
	uart_int( 9600 );								//Initializing UART with baud rate 9600
	adc_int( AD0_0 );								//initializing ADC for POT input
	return 0;
}
