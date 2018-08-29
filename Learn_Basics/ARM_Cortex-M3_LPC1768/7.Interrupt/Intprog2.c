#include <lpc17xx.h>   

#define PINSEL_EINT0    20
#define PINSEL_EINT1    22

#define LED1            16   
#define LED2            17    

#define SBIT_EINT0      0
#define SBIT_EINT1      1  

#define SBIT_EXTMODE0   0
#define SBIT_EXTMODE1   1

#define SBIT_EXTPOLAR0  0
#define SBIT_EXTPOLAR1  1


void EINT0_IRQHandler(void)
{
    LPC_SC->EXTINT = (1<<SBIT_EINT0);  /* Clear Interrupt Flag */
    LPC_GPIO0->FIOPIN ^= (1<< LED1);   /* Toggle the LED1 everytime INTR0 is generated */
}


int main()
{
    SystemInit();

    LPC_SC->EXTINT      = (1<<SBIT_EINT0);	    /* Clear Pending interrupts */
    LPC_PINCON->PINSEL4 = (1<<PINSEL_EINT0);   /* Configure P2_10,P2_11 as EINT0/1 */
    LPC_SC->EXTMODE     = (1<<SBIT_EXTMODE0) | (1<<SBIT_EXTMODE1);  /* Configure EINTx as Edge Triggered*/
    LPC_SC->EXTPOLAR    = (1<<SBIT_EXTPOLAR0)| (1<<SBIT_EXTPOLAR0); /* Configure EINTx as Falling Edge */

    LPC_GPIO0->FIODIR   = (1<<LED1);                   /* Configure LED pins as OUTPUT */
    LPC_GPIO0->FIOPIN   =  0x00;

    NVIC_EnableIRQ(EINT0_IRQn);    /* Enable the EINT0,EINT1 interrupts */

    while(1)
    {
      // Do nothing
    }      
}