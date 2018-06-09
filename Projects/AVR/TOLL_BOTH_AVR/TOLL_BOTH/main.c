/*
 * TOLL_BOTH.c
 *
 * Created: 13-07-2017 06:50:46 PM
 * Author : ASWIN
 */ 

#include<avr/io.h>
#include<util/delay.h>
void cmd(int);
void data(char);
void display(const char *);
int password();
char key();
void motor();

int main()
{
	int p;
	DDRA=0X00;
    DDRB=0XFF;
	DDRC=0XFF;
	DDRD=0XF0;
	cmd(0X38);
	cmd(0X80);
	cmd(0X06);
	cmd(0X0E);
	h:cmd(0X01);
	display("WELCOME");
	_delay_ms(5000);
	cmd(0X01);
	display("PRESS THE BUTTON");
	while((PINA&0X01)!=1);
	if((PINA&0X01)==1)
	{
		p=password();
		if(p==1)
		{
			motor();
		}
		else
		{
			goto h;
		}
	}
}

void cmd(int a)
{
	PORTC=a;
	PORTB=0X02;
	_delay_ms(5000);
	PORTB=0X00;
}

void data(char b)
{
	PORTC=b;
	PORTB=0X03;
	_delay_ms(5000);
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

int password()
{
	char a[4],b[4]="1234";
	int c=0,i;
	cmd(0X01);
	display("ENTER THE PASSWORD");
	_delay_ms(3000);
	cmd(0X01);
	for(i=0;i<4;i++)
	{
		a[i]=key();
		_delay_ms(1000);
		data(a[i]);
	}
	for(i=0;i<4;i++)
	{
		if(a[i]==b[i])
		{
			c++;
		}
	}
	if(c==4)
	{
		cmd(0X01);
		display("ACCESS GRANTED");
		return 1;
	}
	else
	{
		cmd(0X01);
		display("ACCESS DENIED");
		return 0;
	}
}

char key()
{
	int e;
	while(1)
	{
		PORTD=0X7F;
		e=PIND&0X0F;
		switch(e)
		{
			case 0X07:
			return('1');
			break;
			case 0X0B:
			return('2');
			break;
			case 0X0D:
			return('3');
			break;
			case 0X0E:
			return('4');
			break;
		}
		PORTD=0XBF;
		e=PIND&0X0F;
		switch(e)
		{
			case 0X07:
			return('5');
			break;
			case 0X0B:
			return('6');
			break;
			case 0X0D:
			return('7');
			break;
			case 0X0E:
			return('8');
			break;
		}
		PORTD=0XDF;
		e=PIND&0X0F;
		switch(e)
		{
			case 0X07:
			return('9');
			break;
			case 0X0B:
			return('*');
			break;
			case 0X0D:
			return('#');
			break;
			case 0X0E:
			return('0');
			break;
		}
		PORTD=0XEF;
		e=PIND&0X0F;
		switch(e)
		{
			case 0X07:
			return('H');
			break;
			case 0X0B:
			return('A');
			break;
			case 0X0D:
			return('R');
			break;
			case 0X0E:
			return('O');
			break;
		}
	}
}

void motor()
{
	while(1)
	{
		PORTB=0X50;
	}
}