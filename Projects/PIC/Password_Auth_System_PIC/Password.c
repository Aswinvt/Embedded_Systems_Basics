#include<pic.h>
void cmd(int);
void data(char);
void display(const char *);
char key();
void delay();
void main()
{
	char a[4]="1234",b[4];
	int i,c=0;
	TRISC=0X00;
	TRISD=0X00;
	TRISB=0X0F;
	cmd(0X38);
	cmd(0X80);
	cmd(0X01);
	cmd(0X06);
	cmd(0X0E);

	 for(i=0;i<4;i++)
	{
		b[i]=key();
		data(b[i]);
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
		display("Access Granted");
	}
	else
	{
		cmd(0X01);
		display("Wrong");
	}
}
char key()
{
		int e;
		while(1)
		{
			PORTB=0X7F;
			e=PORTB&0X0F;
			switch(e)
				{
					case 0X07:
					return('1');

					case 0X0B:
			    	return('2');

					case 0X0D:
					return('3');

					case 0X0E:
					return('4');
				}
			PORTB=0XBF;
			e=PORTB&0X0F;
			switch(e)
			{
				case 0X07:
				return('5');

				case 0X0B:
				return('6');

				case 0X0D:
				return('7');

				case 0X0E:
				return('8');
			}
		PORTB=0XDF;
		e=PORTB&0X0F;
		switch(e)
		{
			case 0X07:
			return('9');

			case 0X0B:
			return('0');

			case 0X0D:
			return('*');

			case 0X0E:
			return('#');
		}
		PORTB=0XEF;
		e=PORTB&0X0F;
		switch(e)
		{
			case 0X07:
			return('A');

			case 0X0B:
			return('B');

			case 0X0D:
			return('C');

			case 0X0E:
			return('D');
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
	for(i=0;i<500;i++)
	for(j=0;j<500;j++);
}
