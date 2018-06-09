#include<avr/io.h>
#include<util/delay.h>
void timer();
void main()
{
	DDRD=0XFF;
	TCCR1B=0X03;
	TCNT1H=0XFF;
	TCNT1L=0XFF;
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
	while((TIFR&0X40)==0);
}
