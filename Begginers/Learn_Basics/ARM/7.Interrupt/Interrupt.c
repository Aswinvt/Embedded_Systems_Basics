#include<lpc21xx.h>
void delay();

__irq void blink()
{	
	IO1SET=0XFFFF0000;
	delay();
	IO1CLR=0XFFFF0000;
	delay();
	EXTINT=0X01;	
}

void main()
{
	IO1DIR=0XFFFFFFFF;
	IO0DIR=0X00000000;
	PINSEL0=0X0000000C;
	VICIntEnable=0X00004000;
	VICVectCntl0=0X0000002E;
	EXTINT=0X01;		 
	VICVectAddr0=(unsigned)blink;
	while(1)
	{
		IO1SET=0XFF000000;
		delay();
		IO1CLR=0XFF000000;
		delay();	  
	}
}

void delay()
{
	int i,j;
	for(i=0;i<1500;i++)
	for(j=0;j<500;j++);
}
