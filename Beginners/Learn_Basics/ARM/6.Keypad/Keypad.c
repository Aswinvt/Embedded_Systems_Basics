#include<LPC21XX.h>
void cmd(int);
void data(char);
void delay();
void display(const char *);
char key();

void main()
{
	char a;
	IO0DIR=0XFFFFFFFF;
	IO1DIR=0X00F00000;
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

void cmd(int a)
{
	IO0CLR=0XFFFFFFFF;
	IO0SET=a;
	delay();
	IO0SET=0X00000200;
	delay();
	IO0CLR=0X00000200;
}

void data(char b)
{
	IO0CLR=0XFFFFFFFF;
	IO0SET=b;
	delay();
	IO0SET=0X00000300;
	delay();
	IO0CLR=0X00000200;
}

void display(const char *p)
{
	while(*p!='\0')
	{
		data(*p);
		p++;
	}
}

char key()
{
	int e;
	while(1)
	{
		IO0CLR=0XFFFFFFFF;
		IO1CLR=0XFFFFFFFF;
		IO1SET=0X007F0000;
		e=IO1PIN&0X000F0000;
		switch(e)
		{
			case 0X00070000:
			return('1');
			case 0X000B0000:
			return('2');
			case 0X000D0000:
			return('3');
			case 0X000E0000:
			return('4');
		}
		IO0CLR=0XFFFFFFFF;
		IO1CLR=0XFFFFFFFF;
		IO1SET=0X00BF0000;
		e=IO1PIN&0X000F0000;
		switch(e)
		{
			case 0X00070000:
			return('5');
			case 0X000B0000:
			return('6');
			case 0X000D0000:
			return('7');
			case 0X000E0000:
			return('8');
		}
		IO0CLR=0XFFFFFFFF;
		IO1CLR=0XFFFFFFFF;
		IO1SET=0X00DF0000;
		e=IO1PIN&0X000F0000;
		switch(e)
		{
			case 0X00070000:
			return('9');
			case 0X000B0000:
			return('*');
			case 0X000D0000:
			return('0');
			case 0X000E0000:
			return('#');
		}
		IO0CLR=0XFFFFFFFF;
		IO1CLR=0XFFFFFFFF;
		IO1SET=0X00EF0000;
		e=IO1PIN&0X000F0000;
		switch(e)
		{
			case 0X00070000:
			return('A');
			case 0X000B0000:
			return('B');
			case 0X000D0000:
			return('C');
			case 0X000E0000:
			return('D');
		}
	}
}

void delay()
{
	int i,j;
	for(i=0;i<455;i++)
	for(j=0;j<450;j++);
}
