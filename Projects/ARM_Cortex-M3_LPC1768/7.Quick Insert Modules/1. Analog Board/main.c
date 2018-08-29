/*
 * File name            : main.c
 * Compiler             : MDK-Lite
 * IDE                  : Keil uVision V5
 * Author               : Etiq Technologies
 * Processor            : LPC1768
 * Created on           : November 20, 2017, 01:20 PM
 * Description          : Program for Analog Addon board interface
 */
 
#include "adc.h"

int main()
{
	TIMER_Init();										//Timer Initialization
	PWM_Init( PIN1_18, 500 );				//Set Port1 18th pin as pwm for LED control
	uart_int( 9600 );								//Initializing UART with baud rate 9600
	adc_int( AD0_0 );								//initializing ADC for POT input
	return 0;
}
