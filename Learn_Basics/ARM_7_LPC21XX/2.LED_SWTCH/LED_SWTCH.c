#include<LPC21XX.h>
void delay();

void main()
{
	int i,run;
	IO0DIR=0XFFFFFFF0;
	while(1)
	{
		if((IO0PIN&0X00000001)==0)
		{
			IO0SET=0XFFFFFFF0;
			delay();
			IO0CLR=0XFFFFFFF0;
			delay();
		}
		else if((IO0PIN&0X00000002)==0)
		{
			IO0SET=0X0000FFF0;
			delay();
			IO0CLR=0X0000FFF0;
			delay();
			IO0SET=0XFFFF0000;
			delay();
			IO0CLR=0XFFFF0000;
			delay();
		}
		else if((IO0PIN&0X00000004)==0)
		{
			i=0,run=0X0000010;
			while(i<28)
			{
				IO0SET=run;
				delay();
				IO0CLR=run;
				delay();
				run=run<<1;
				i++;
			}
		}
		else if((IO0PIN&0X00000008)==0)
		{
			i=0,run=0X8000000;
			while(i<28)
			{
				IO0SET=run;
				delay();
				IO0CLR=run;
				delay();
				run=run>>1;
				i++;
			}
		}
	}
}

void delay()
{
	int i,j;
	for(i=0;i<355;i++)
	for(j=0;j<350;j++);
}
