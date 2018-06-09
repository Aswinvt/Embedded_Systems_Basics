#include<pic.h>
void delay();
void main()
{
	int i;
	TRISB=0XFF;
	TRISD=0X00;
	while(1)
	{
		if(RB0==1)
		{
			PORTD=0XFF;
			delay();
			PORTD=0X00;
			delay();
		}
		else if(RB1==1)
		{
			PORTD=0X0F;
			delay();
			PORTD=0XF0;
			delay();
		}
		else if(RB2==1)
		{
			PORTD=0X55;
			delay();
			PORTD=0XAA;
			delay();
		}
		else if(RB3==1)
		{
			PORTD=0X01;
			delay();
			for(i=0;i<8;i++)
			{
				PORTD=PORTD<<1;
				delay();
			}
		}
		else if(RB4==1)
		{
			PORTD=0X80;
			delay();
			for(i=0;i<8;i++)
			{
				PORTD=PORTD>>1;
				delay();
			}
		}
	}
}
void delay()
{
	int i,j;
	for(i=0;i<255;i++)
	for(j=0;j<250;j++);
}


