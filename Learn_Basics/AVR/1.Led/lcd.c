#include<avr/io.h>
#include<util/delay.h>
void cmd(int a);
void data(char b);
void display(const char *);
void main()
{
	DDRD=0XFF;
	DDRB=0XFF;
	cmd(0X38);
	cmd(0X01);
	cmd(0X80);
	cmd(0X06);
	cmd(0X0E);
	display("hai");
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
void display(const char *p)
{
	while(*p!='\0')
	{
		data(*p);
		p++;
	}
}
