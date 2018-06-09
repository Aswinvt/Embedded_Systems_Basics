#include<avr/io.h>
#include<util/delay.h>
void timer();
void main()
{
	DDRD=0XFF;
	TCCR0=0X05;
	TCNT0=0X00;
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
	while((TIFR&0X01)==0);
}
