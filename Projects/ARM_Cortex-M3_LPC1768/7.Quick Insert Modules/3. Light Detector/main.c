/*
 * File name            : main.c
 * Compiler             : MDK-Lite
 * IDE                  : Keil uVision V5
 * Author               : Etiq Technologies
 * Processor            : LPC1768
 * Created on           : November 20, 2017, 02:19 PM
 * Description          : Program for Light Detector board interface
 */
 
#include "adc.h"

int main()
{
	uart_int(9600);										//Initializing UART with baud rate 9600
	adc_int(AD0_0);										//Initializing ADC for Light detector input
	return 0;
}
