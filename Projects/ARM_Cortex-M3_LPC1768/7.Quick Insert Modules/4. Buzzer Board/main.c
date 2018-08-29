/*
 * File name            : main.c
 * Compiler             : MDK-Lite
 * IDE                  : Keil uVision V5
 * Author               : Etiq Technologies
 * Processor            : LPC1768
 * Created on           : November 20, 2017, 05:34 PM
 * Description          : Program for Buzzer Addon board interface
 */
 
#include "update.h"

int main()
{
	TIMER_Init();										//Initializing Timer
	PWM_Init( PIN1_18, 2000 );			//Initializing PWM output for buzzzer control
	update_pwm();										//PWM varies with button(Port0 16th and 17th) press to controll sound
	while(1)
	{
		
	}
}
