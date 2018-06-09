#include<avr/io.h>
#include<util/delay.h>
void cmd(int a);
void data(char b);
void main()
{
	int a,b,c,d;
	DDRA=0X00;
	DDRB=0XFF;
	DDRD=0XFF;
	cmd(0X38);
	cmd(0X80);
	cmd(0X06);
	cmd(0X0E);
	cmd(0X01);
	ADMUX=0X60;
	while(1)
	{
		ADCSRA=0XC0;
		while((ADCSRA&0X40)==1);
		a=ADCH;
		b=(a/100)+48;
		data(b);
		c=((a%100)/10)+48;
		data(c);
		d=(a%10)+48;
		data(d);
		cmd(0X01);
	}
}
void cmd(int a)
{
	PORTB=a;
	PORTD=0X40;
	_delay_ms(500);
	PORTD=0X00;
}
void data(char b)
{
	PORTB=b;
	PORTD=0X60;
	_delay_ms(500);
	PORTD=0X20;
}
