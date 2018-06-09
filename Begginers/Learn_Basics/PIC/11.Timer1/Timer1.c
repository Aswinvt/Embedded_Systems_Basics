#include<pic.h>
void timer();
void main()
{
	TRISD=0X00;
	T1CON=0X09;
	TMR1H=0X00;
	TMR1L=0X00;
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
	while(TMR1IF==0);
	TMR1IF=0;
}
