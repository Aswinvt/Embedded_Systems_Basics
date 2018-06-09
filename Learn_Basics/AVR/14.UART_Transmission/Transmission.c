#include<avr\io.h>
#include<util\delay.h>
void trans(char);
char rec();
void main()
{
	char a[10];
	int i;
	DDRB=0XFF;
	DDRC=0XFF;
	DDRD=0X02;
	UCSRA=0X00;
	UCSRB=0X18;
	UCSRC=0X06;
	UBRRL=0X33;
	UBRRH=0X00;
	while(rec()!='*');
	for(i=0;a[i-1]!='#';i++)
	{
		a[i]=rec();
	}
	a[i-1]='\0';
	for(i=0;a[i]!='\0';i++)
	{
		trans(a[i]);
	}	
}
char rec()
{
	while((UCSRA&0X80)==0);
	return(UDR);
}
void trans(char b)
{
	UDR=b;
	while((UCSRA&0X40)==0);
	_delay_ms(500);
}
