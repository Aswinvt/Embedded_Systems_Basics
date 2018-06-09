#include<pic.h>
void cmd(int);
void data(char);
char key();
void delay();
void main()
{
	int a;
	TRISB=0X0F;
	TRISC=0X00;
	TRISD=0X00;
	cmd(0X38);
	cmd(0X80);
	cmd(0X01);
	cmd(0X06);
	cmd(0X0E);
	while(1)
	{
		a=key();
		data(a);
	}
}
char key()
{
	int e;
	while(1)
	{
		PORTB=0X7F;
		e=PORTB&0X0F;
		switch(e)
		{
			case 0X07:
			return('1');
			case 0X0B:
			return('2');
			case 0X0D:
			return('3');
			case 0X0E:
			return('4');
		}
		PORTB=0XBF;
		e=PORTB&0X0F;
		switch(e)
		{
			case 0X07:
			return('5');
			case 0X0B:
			return('6');
			case 0X0D:
			return('7');
			case 0X0E:
			return('8');
		}
		PORTB=0XDF;
		e=PORTB&0X0F;
		switch(e)
		{
			case 0X07:
			return('9');
			case 0X0B:
			return('0');
			case 0X0D:
			return('A');
			case 0X0E:
			return('B');
		}
		PORTB=0XDF;
		e=PORTB&0X0F;
		switch(e)
		{
			case 0X07:
			return('C');
			case 0X0B:
			return('D');
			case 0X0D:
			return('E');
			case 0X0E:
			return('G');
		}
		PORTB=0XEF;
		e=PORTB&0X0F;
		switch(e)
		{
			case 0X07:
			return('H');
			case 0X0B:
			return('I');
			case 0X0D:
			return('*');
			case 0X0E:
			return('#');
		}
	}
}
void cmd(int a)
{
	PORTD=a;
	RC0=0;	
	RC1=1;
	delay();
	RC1=0;
}
void data(char b)
{
	PORTD=b;
	RC0=1;
	RC1=1;
	delay();
	RC1=0;
}
void delay()
{
	int i,j;
	for(i=0;i<500;i++)
	for(j=0;j<500;j++);
}
