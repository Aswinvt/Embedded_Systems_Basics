#include<pic.h>
void cmd(int);
void data(char);
void display(const char *);
void delay();
void main()
{
	TRISB=0X00;
	TRISC=0XF0;
	TRISD=0X00;
	cmd(0X38);
	cmd(0X80);
	cmd(0X06);
	cmd(0X0E);
	cmd(0X01);
	while(1)
	{
		if(RC4==0)
		{
			PORTB=0X1D;
			display("FORWARD");
			cmd(0X01);
		}
		else if(RC5==0)
		{
			PORTB=0X2E;
			display("BACKWARD");
			cmd(0X01);
		}
		else if(RC6==0)
		{
			PORTB=0X00;
			display("STOP");
			cmd(0X01);
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
