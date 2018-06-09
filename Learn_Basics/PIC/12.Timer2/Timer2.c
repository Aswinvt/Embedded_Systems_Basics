#include<pic.h>
void timer();
void main()
{
	TRISD=0X00;
	T2CON=0X7C;
	TMR2=0X00;
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
	while(TMR2IF==0);
	TMR2IF=0;
}

