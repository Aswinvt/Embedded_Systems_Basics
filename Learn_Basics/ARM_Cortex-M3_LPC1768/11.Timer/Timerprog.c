#include<lpc17xx.h>

int main()
{
	unsigned int pclk, PreScale, ReqCntsPerSec;
	SystemInit();
	
	LPC_SC->PCONP |= (1<<1);
	LPC_TIM0->MCR = (1<<0)|(1<<1);
	
	pclk = (LPC_SC->PCLKSEL0 >> 2) & 0x03;
	
	LPC_TIM0->MR0 = 1000000;
	
	switch(pclk)
	{
    case 0x00: pclk = SystemCoreClock/4;
							 break;

    case 0x01: pclk = SystemCoreClock;
							 break; 

    case 0x02: pclk = SystemCoreClock/2;
							 break; 

    case 0x03: pclk = SystemCoreClock/8;
							 break;		
	}
	
	ReqCntsPerSec	= 1000000;
	
	PreScale = pclk/ReqCntsPerSec;
	LPC_TIM0->PR = PreScale - 1;
	
	LPC_TIM0->TCR = (1<<0);
	
	LPC_GPIO0->FIODIR = (1<<0);
	NVIC_EnableIRQ(TIMER0_IRQn);
	
	while(1);
}
	
void TIMER0_IRQHandler(void)
{
    uint8_t interrupt_bit;
    interrupt_bit = LPC_TIM0->IR;
    LPC_TIM0->IR = interrupt_bit;
    LPC_GPIO0->FIOPIN ^= (1<<0);
}
