#include "delay_ms.h"

void DELAY_ms(double x)
{
	unsigned int pclk, PreScale, ReqCntsPerSec;
	uint8_t interrupt_bit;
	
	LPC_SC->PCONP |= (1<<1);
	LPC_TIM0->MCR = (1<<0)|(1<<1);
	
	LPC_TIM0->MR0 = x*1000;
	
	pclk = SystemCoreClock/4;		
	
	ReqCntsPerSec	= 1000000;
	
	PreScale = pclk/ReqCntsPerSec;
	LPC_TIM0->PR = PreScale - 1;
	
	LPC_TIM0->TCR = (1<<0);
	
	while(LPC_TIM0->IR!=1);
	interrupt_bit = LPC_TIM0->IR;
  LPC_TIM0->IR = interrupt_bit;
}
