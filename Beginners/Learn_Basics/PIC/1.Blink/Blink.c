#include<pic.h>
void delay();
void main()
{
	int i;
	TRISD=0X00;
	while(1)
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
void delay()
{
	int i,j;
	for(i=0;i<200;i++)
	for(j=0;j<200;j++);
}



