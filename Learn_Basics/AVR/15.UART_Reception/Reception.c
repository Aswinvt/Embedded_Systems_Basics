#include<avr\io.h>
#include<util\delay.h>
void trans(char);
char rec();
void cmd(int);
void data(char);
void main()
{
	char a;
	DDRB=0XFF;
	DDRC=0XFF;
	DDRD=0XF2;
	UCSRA=0X00;
	UCSRB=0X18;
	UCSRC=0X06;
	UBRRL=0X33;
	UBRRH=0X00;
	cmd(0X38);
	cmd(0X80);
	cmd(0X06);
	cmd(0X0E);
	cmd(0X01);
	while(1)
	{
		a=rec();
		data(a);
		trans(a);
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

void cmd(int c)
{
	PORTB=c;
	PORTD=0X40;
	_delay_ms(500);
	PORTD=0X00;
}

void data(char d)
{
	PORTB=d;
	PORTD=0X60;
	_delay_ms(500);
	PORTD=0X20;
}
