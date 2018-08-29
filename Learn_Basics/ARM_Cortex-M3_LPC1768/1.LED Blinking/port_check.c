#include<lpc17xx.h>											// Header file for LPC17XX series controller

void delay(void);												// Declaration for delay function

int main()
{
	SystemInit();													// Initializes the microcontroller system
	LPC_GPIO0->FIODIR = 0XFFFFFFFF;				// Initializing direction Port 0 as output
	LPC_GPIO1->FIODIR = 0XFFFFFFFF;				// Initializing direction Port 1 as output
	while(1)
	{
		LPC_GPIO0->FIOSET = 0XFFFFFFFF;			// Setting Port 0 a high value for LED on state
		LPC_GPIO1->FIOSET = 0XFFFFFFFF;			// Setting Port 1 a high value for LED on state
		delay();														// calling delay function
		LPC_GPIO0->FIOCLR = 0XFFFFFFFF;			// Setting Port 0 a low value for LED off state
		LPC_GPIO1->FIOCLR = 0XFFFFFFFF;			// Setting Port 1 a low value for LED off state
		delay();
	}
}/*End of main*/

void delay()
{
	int i,j;
	for(i=0;i<3000;i++)
	{
		for(j=0;j<3000;j++);
	}
}/*End of delay*/
