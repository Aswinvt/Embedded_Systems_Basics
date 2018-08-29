/*
 * File name            : main.c
 * Compiler             : MDK-Lite
 * IDE                  : Keil uVision V5
 * Author               : Etiq Technologies
 * Processor            : LPC1768
 * Created on           : November 20, 2017, 02:40 PM
 * Description          : Program for Proximity Addon board interface
 */
 
#include "adc.h"

int main()
{
	TIMER_Init();									//Initializing Timer
	PWM_Init( PIN1_18, 200 );			//Initializing PWM for IR transmitter
	uart_int( 9600);							//Initializing UART with baud rate 9600
	adc_int(AD0_0);								//Initializing ADC for IR receiver
	return 0;
}
