#include<LPC21XX.h>
void delay();

void main()
{
	int i=0,run=0X0000001;
	IO0DIR=0XFFFFFFFF;
	while(1)
	{
		i=0,run=0X0000001;
		while(i<32)
		{
			IO0SET=run;
			delay();
			IO0CLR=run;
			delay();
			run=run<<1;
			i++;
		}
	}
}

void delay()
{
	int i,j;
	for(i=0;i<355;i++)
	for(j=0;j<350;j++);
}
