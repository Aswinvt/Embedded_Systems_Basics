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
			display("FORWARD");
			while((IO1PIN&0X00010000)==0)
			{
				IO0SET=0XFFFDFFFF;
			}
			cmd(0X01);
		}
		else if((IO1PIN&0X00020000)==0)
		{
			cmd(0X01);
			display("REVERSE");
			while((IO1PIN&0X00020000)==0)
			{
				IO0SET=0XFFFEFFFF;
			}
			cmd(0X01);
		}
		else if((IO1PIN&0X00040000)==0)
		{						  
			cmd(0X01);
			display("STOP");
			while((IO1PIN&0X00040000)==0)
			{
				IO0SET=0XFFF0FFFF;
			}
			cmd(0X01);
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
	for(i=0;i<255;i++)
	for(j=0;j<250;j++);
}
