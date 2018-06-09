#include<pic.h>
void cmd(int);
void data(char);
void display(const char *);
void delay();
void main()
{	
	int i;
	TRISB=0X00;
	TRISD=0X00;
	TRISC=0XF0;
	cmd(0X38);
	cmd(0X80);
	cmd(0X01);
	cmd(0X06);
	cmd(0X0E);
	while(1)
	{
		if(RC4==0)
		{
			PORTB=0XFF;
			delay();
			PORTB=0X00;
			delay();
			display("BLINKING");
			cmd(0X01);
		}
		else if(RC5==0)
		{
			PORTB=0X0F;
			delay();
			PORTB=0XF0;
			delay();
			display("4BY4");
			cmd(0X01);
		}
		else if(RC6==0)
		{
			PORTB=0XAA;
			delay();
			PORTB=0X55;
			delay();
			display("ALTERNATE");
			cmd(0X01);
		}
		else if(RC7==0)
		{
			PORTB=0X01;
			cmd(0X01);
			display("UP-DOWN");
			delay();
			for(i=0;i<8;i++)
			{
				PORTB=PORTB<<1;
				delay();
			}
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
