#include<avr/io.h>
#include<util/delay.h>
void trans(char);
void main()
{
	int i;
	char a[]="SMEC";
	DDRD=0X02;
	UCSRA=0X00;
	UCSRB=0X18;
	UCSRC=0X06;
	UBRRL=0X33;
	UBRRH=0X00;
	for(i=0;a[i]!='\0';i++)
	{
		trans(a[i]);
	}
	
}

void trans(char b)
{
	UDR=b;
	while((UCSRA&0X40)==0);
	_delay_ms(500);
}
