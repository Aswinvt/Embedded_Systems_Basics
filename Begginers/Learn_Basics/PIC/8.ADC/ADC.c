#include<pic.h>
void delay();
void cmd(int);
void data(char);
void main()
{
	char a,b,c,d;
	cmd(0X38);
	cmd(0X80);
	cmd(0X01);
	cmd(0X06);
	cmd(0X0E);
	TRISD=0X00;
	TRISA=0XFF;
	TRISB=0X00;
	ADCON0=0X01;
	ADCON1=0X00;
	ADGO=1;
	while(ADGO==1);
	a=ADRESH;
	b=((a/100)+48);
	data(b);
	c=(((a%100)/10)+48);
	data(c);
	d=((a%10)+48);
	data(d);
	delay();
	cmd(0X01);
}
void cmd(int a)
{
	PORTD=a;
	RB0=0;
	RB1=1;
	delay();
	RB1=0;
}
void data(char b)
{
	PORTD=b;
	RB0=1;
	RB1=1;
	delay();
	RB1=0;
}
void delay()
{
	int i,j;
	for(i=0;i<155;i++)
	for(j=0;j<150;j++);
}
