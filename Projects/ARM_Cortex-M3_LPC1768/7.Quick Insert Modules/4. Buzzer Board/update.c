/*
 * File name            : main.c
 * Compiler             : MDK-Lite
 * IDE                  : Keil uVision V5
 * Author               : Etiq Technologies
 * Processor            : LPC1768
 * Created on           : November 20, 2017, 01:20 PM
 * Description          : Program for PWM dutycycle variation
 */
 
#include "update.h"

void update_pwm()
{
	int c=0, x=0;
	GPIO_SetPinDir(PIN0_16,INPUT);
	GPIO_SetPinDir(PIN0_17,INPUT);
	GPIO_SetPinDir(PIN0_18,OUTPUT);
	while(1)
	{
		if(c<2000)
		{
			if(!GPIO_GetPinVal(PIN0_16))
			{
				while(!GPIO_GetPinVal(PIN0_16));
				GPIO_SetPinVal(PIN0_18,x^=1);
				c+=50;
			}
		}
		if(c>0)
		{
			if(!GPIO_GetPinVal(PIN0_17))
			{
				while(!GPIO_GetPinVal(PIN0_17));
				GPIO_SetPinVal(PIN0_18,x^=1);
				c-=50;
			}
		}
		PWM_UpdatePulseWidth(c);
	}
}
