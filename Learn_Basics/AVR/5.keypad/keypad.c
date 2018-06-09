#include<avr/io.h>
#include<util/delay.h>
void cmd(int);
void data(char);
void main()
{
	
	int e;
	DDRD=0XF0;
	DDRC=0XFF;
	DDRB=0XFF;
	cmd(0X38);
	cmd(0X80);
	cmd(0X0E);
	cmd(0X06);
	cmd(0X01);
	while(1)
	{
		PORTD=0X7F;
		e=PIND&0X0F;
		switch(e)
		{
			case 0X07:
			data('1');
			break;

			case 0X0B:
			data('2');
			break;

			case 0X0D:
			data('3');
			break;

			case 0X0E:
			data('4');
			break;
		}
 
		PORTD=0XBF;
		e=PIND&0X0F;
		switch(e)
		{
			case 0X07:
			data('5');
			break;

			case 0X0B:
			data('6');
			break;

			case 0X0D:
			data('7');
			break;

			case 0X0E:
			data('8');
			break;
		}

		PORTD=0XDF;
		e=PIND&0X0F;
		switch(e)
		{
			case 0X07:
			data('9');
			break;

			case 0X0B:
			data('*');
			break;

			case 0X0D:
			data('#');
			break;

			case 0X0E:
			data('0');
			break;
		}

		PORTD=0XEF;
		e=PIND&0X0F;
		switch(e)
		{
			case 0X07:
			data('H');
			break;

			case 0X0B:
			data('A');
			break;

			case 0X0D:
			data('R');
			break;

			case 0X0E:
			data('O');
			break;
		}
	}
}
void cmd(int a)
{
	PORTB=a;
	PORTC=0X02;
	_delay_ms(2000);
	PORTC=0X00;
}

void data(char b)
{
	PORTB=b;
	PORTC=0X03;
	_delay_ms(2000);
	PORTC=0X01;
}
