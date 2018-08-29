#include<lpc17xx.h>
void delay();

int main()
{
	SystemInit();
	LPC_GPIO0->FIODIR = 0XFFFFFFFF;
	//LPC_GPIO1->FIODIR = (1<<24);
	while(1)
	{
//		LPC_GPIO0->FIOSET = 0XFFFFFFFF;
//		delay();
//		LPC_GPIO0->FIOCLR = 0XFFFFFFFF;
//		delay();
//		LPC_GPIO1->FIOSET = 0XFFFFFFFF;
//		delay();
//		LPC_GPIO1->FIOCLR = 0XFFFFFFFF;
//		delay();
		while((LPC_GPIO1->FIOPIN >> 31) & 0x01);
		while(!((LPC_GPIO1->FIOPIN >> 31) & 0x01));

		LPC_GPIO0->FIOSET = 0XFFFFFFFF;
		delay();
		LPC_GPIO0->FIOCLR = 0XFFFFFFFF;
		delay();
		
		
	}
return 0;
}

void delay()
{
	int i,j;
	for(i=0;i<5000;i++)
	{
		for(j=0;j<500;j++);
	}
}