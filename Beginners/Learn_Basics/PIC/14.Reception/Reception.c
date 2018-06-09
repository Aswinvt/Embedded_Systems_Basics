#include<pic.h>
void delay();
void trans(char);
char rec();
void cmd(int);
void data(char);
void main()
{
	char a;
	TRISB=0X00;
	TRISD=0X00;
	TRISC=0X80;
	TXSTA=0X24;
	RCSTA=0X90;
	SPBRG=129;
	cmd(0X38);
	cmd(0X01);
	cmd(0X06);
	cmd(0X0E);
	cmd(0X80);
	while(1)
	{
		a=rec();
		data(a);
		trans(a);
	}
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
	for(i=0;i<255;i++)
	for(j=0;j<250;j++);
}
void trans(char c)
{
	TXREG=c;
	while(TXIF==0);
	TXIF=0;
}
char rec()
{
	while(RCIF==0);
	return(RCREG);
}
