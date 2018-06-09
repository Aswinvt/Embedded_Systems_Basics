#include<pic.h>
void timer();
void main()
{
	TRISD=0X00;
	OPTION=0X07;
	TMR0=0X00;
	while(1)
	{
		PORTD=0XFF;
		timer();
		PORTD=0X00;
		timer();
	}
}
void timer()
{
	while(TMR0IF==0);
	TMR0IF=0;
}
