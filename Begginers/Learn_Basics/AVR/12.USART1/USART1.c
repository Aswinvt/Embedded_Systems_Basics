#include<avr/io.h>
#include<util/delay.h>
void main()
{
	DDRD=0X02;
	UCSRA=0X00;
	UCSRB=0X18;
	UCSRC=0X06;
	UBRRL=0X33;
	UBRRH=0X00;
	UDR='A';
	while((UCSRA&0X40)==0);
	_delay_ms(300);
}
