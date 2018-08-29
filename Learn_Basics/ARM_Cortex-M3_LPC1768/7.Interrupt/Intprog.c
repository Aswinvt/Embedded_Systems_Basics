#include <lpc17xx.h>

/*EXTIN0 P2.10 ISP*/

#define 	EINT_FUNC				 0x01
#define		EINT_CLR				 0x11
#define		EINT_0					 20
#define		EINT_1					 22
#define		EINT_2					 24
#define		EINT_3					 26

#define		LEVEL_SENSE		 	 0
#define		EDGE_SENSE		 	 1

#define		POL_LOWFALL 		 0
#define		POL_HIGHRISE 		 1

#define		EXTINT0					 0
#define		EXTINT1					 1
#define		EXTINT2					 2
#define		EXTINT3					 3

void EINT0_IRQHandler (void) 
{
	static int LED = 0;	
	LPC_SC->EXTINT |= (1<<EXTINT0); // Clear External interrupt flag
	/*Toggle LED*/
	LED = ~LED;	
	if(LED)
  		LPC_GPIO0->FIOSET  = (1<<16);
	else  
 		LPC_GPIO0->FIOCLR  = (1<<16);	
}

int main()
{
	SystemInit();
	LPC_GPIO0->FIODIR |= (1<<16); // Set LED pin as output
	
	LPC_PINCON->PINSEL4 &= ~(EINT_CLR << EINT_0); // Clear bits
	LPC_PINCON->PINSEL4 |= (EINT_FUNC << EINT_0); // Changing pin function to External Interrupt
	
	LPC_SC->EXTMODE |= EDGE_SENSE; // Edge Sensing
	LPC_SC->EXTPOLAR|= POL_LOWFALL; // Falling Edge
	
	NVIC_EnableIRQ(EINT0_IRQn); // Enable External interrupt
	
	while(1);
}
