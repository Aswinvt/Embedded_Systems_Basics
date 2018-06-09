#include<avr/io.h>
#include<util/delay.h>
void cmd(int a);
void data(char b);
void display(const char *p);
void main()
{
	int i;
	DDRB=0XFF;
	DDRD=0XFF;
	DDRC=0X00;
	cmd(0X38);
	cmd(0X01);
	cmd(0X80);
	cmd(0X06);
	cmd(0X0E);
	while(1)
	{
		if((PINC&0X01)==0)
		{
			PORTD=0XFF;
			_delay_ms(500);
			PORTD=0X00;
			_delay_ms(500);
			display("BLINKING");
			_delay_ms(1000);
			cmd(0X01);
		}
		else if((PINC&0X02)==0)
		{
			PORTD=0XF0;
			_delay_ms(500);
			PORTD=0X0F;
			_delay_ms(500);
			display("4by4");
			_delay_ms(1000);
			cmd(0X01);
		}
		else if((PINC&0X04)==0)
		{
			PORTD=0XAA;
			
			_delay_ms(500);
			PORTD=0X55;
			_delay_ms(500);
			display("ALTERNATE");
			_delay_ms(1000);
			cmd(0X01);
		}
		else if((PINC&0X08)==0)
		{
			PORTD=0X01;
			_delay_ms(500);
			for(i=0;i<8;i++)
			{
				PORTD=PORTD<<1;
				_delay_ms(500);
			}
			display("UP TO DOWN");
			_delay_ms(1000);
			cmd(0X01);
		}
		else if((PINC&0X10)==0)
		{
			PORTD=0X80;
			_delay_ms(500);
			for(i=0;i<8;i++)
			{
				PORTD=PORTC>>1;
				_delay_ms(500);
			}
			display("DOWN TO UP");
			_delay_ms(1000);
			cmd(0X01);
		}
	}
}
void cmd(int a)
{
	PORTD=a;
	PORTB=0X02;
	_delay_ms(500);
	PORTB=0X00;
}
void data(char b)
{
	PORTD=b;
	PORTB=0X03;
	_delay_ms(500);
	PORTB=0X01;
}
void display(const char *p)
{
	while(*p!='\0')
	{
		data(*p);
		p++;
	}
}
