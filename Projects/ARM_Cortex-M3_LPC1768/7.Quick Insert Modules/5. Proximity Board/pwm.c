/*
 * File name            : main.c
 * Compiler             : MDK-Lite
 * IDE                  : Keil uVision V5
 * Author               : Etiq Technologies
 * Processor            : LPC1768
 * Created on           : November 20, 2017, 01:20 PM
 * Description          : Program for PWM generation
 */
 
#include "pwm.h"

void PWM_Init( uint8_t uiPWMpin, uint16_t uiPWMperiod )
{
	if(uiPWMpin < PIN1_31 )
		GPIO_SetPinFunc( uiPWMpin , 0x2 );
	else if(uiPWMpin > PIN1_31 )
		GPIO_SetPinFunc( uiPWMpin , 0x1 );
	
	LPC_PWM1->PCR = 0x00;			// Single Edge.
	LPC_PWM1->PR = 23;				// Check This. Our PCLK is 24MHz (assumption as 'P' value was not given). Val 23 (i.e. 24MHz - 1) is based on this calculation.
	LPC_PWM1->MR0 = uiPWMperiod;
	LPC_PWM1->MR1 = 50;			// For now, just PWM1.1. This must be changed to a user defined PWM Initialization.
	LPC_PWM1->MCR |= (1 << 1); // Reset TC when MR0 matches
	LPC_PWM1->LER |= (1 << 0) | (1 << 1); //Latch both the registers.

	LPC_PWM1->PCR = (1<<9); //enable PWM output
	LPC_PWM1->TCR = (1<<1); //Reset PWM TC & PR

	LPC_PWM1->TCR = (1<<0) | (1<<3); //enable counters and PWM Mode	
}

void PWM_UpdatePulseWidth( uint16_t uipulsewidth )
{
	LPC_PWM1->MR1 = uipulsewidth; //Update MR1 with new value
	LPC_PWM1->LER |= (1<<1); //Load the MR1 new value at start of next cycle	
}

void TIMER_Init( void )
{
	LPC_TIM0->CTCR = 0x0;
	LPC_TIM0->PR = 25000-1; //Increment TC at every 24999+1 clock cycles
	//25000 clock cycles @25Mhz = 1 mS

	LPC_TIM0->TCR = 0x02; //Reset Timer
}
	
void Delay_ms( uint32_t uimillisec )
{
	LPC_TIM0->TCR = 0x02; //Reset Timer
	LPC_TIM0->TCR = 0x01; //Enable timer

	while(LPC_TIM0->TC < uimillisec); //wait until timer counter reaches the desired delay

	LPC_TIM0->TCR = 0x00; //Disable timer	
	
}
