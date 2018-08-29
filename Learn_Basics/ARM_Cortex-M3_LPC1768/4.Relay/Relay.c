#include<lpc17xx.h>

#define RL 24 // Pin for Realy control

void delay(void);
 
 int main()
 {
	 SystemInit();
	 LPC_GPIO1->FIODIR |= (1<<RL); // Seting direction for Relay pin as output
	 while(1)
	 {
		 LPC_GPIO1->FIOSET = (1<<RL); // Turn on relay
		 delay();
		 LPC_GPIO1->FIOCLR = (1<<RL); // Turn off relay
		 delay();
	 }
 }
 
 void delay(void)
 {
	 int i,j;
	 for(i=0;i<19000;i++)
	 {
		 for(j=0;j<5000;j++);
	 }
 }
