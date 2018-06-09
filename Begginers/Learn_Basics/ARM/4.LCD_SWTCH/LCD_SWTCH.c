#include<LPC21XX.h>
void cmd(int);
void data(char);
void delay();
void display(const char *);

void main()
{
	IO0DIR=0XFFFFFFFF;
	IO1DIR=0X00000000;
	cmd(0X38);
	cmd(0X80);
	cmd(0X01);
	cmd(0X06);
	cmd(0X0E);
	while(1)
	{
		if((IO1PIN&0X00010000)==0)
		{
			cmd(0X01);
			display("PIN 1");
		}
		else if((IO1PIN&0X00020000)==0)
		{
			cmd(0X01);
			display("PIN 2");
		}
		else if((IO1PIN&0X00040000)==0)
		{						  
			cmd(0X01);
			display("PIN 3");
		}
		else if((IO1PIN&0X00080000)==0)
		{
			cmd(0X01);
			display("PIN 4");

		}
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

void delay()
{
	int i,j;
	for(i=0;i<355;i++)
	for(j=0;j<350;j++);
}
