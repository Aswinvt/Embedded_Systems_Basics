#include<LPC21XX.h>
void cmd(int);
void data(char);
void delay();
void display(const char *);

void main()
{
	IO0DIR=0XFFFFFFFF;
	cmd(0X38);
	cmd(0X80);
	cmd(0X01);
	cmd(0X06);
	cmd(0X0E);
	display("HELLO");
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
