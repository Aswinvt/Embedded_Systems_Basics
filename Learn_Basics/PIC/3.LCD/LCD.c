#include<pic.h>
void cmd(int);
void data(char);
void delay();
void display(const char *);
void main()
{
	TRISD=0X00;
	TRISC=0X00;
	cmd(0X38);
	cmd(0X80);
	cmd(0X01);
	cmd(0X06);
	cmd(0X0E);
	display("hai");
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