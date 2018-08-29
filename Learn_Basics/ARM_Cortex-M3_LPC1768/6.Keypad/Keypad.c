#include<lpc17xx.h>

/*Control port*/
#define RS 18
#define RW 17
#define EN 16

/*Data port*/
#define D0 16
#define D1 17
#define D2 18
#define D3 19
#define D4 20
#define D5 21
#define D6 22
#define D7 23

void delay(void);
void _delay(void);
void cmd(int a);
void data(char b);
char key(void);

int main()
{
	char a;
	SystemInit();
	LPC_GPIO1->FIODIR |= (0X0F<<24)|(1<<RS)|(1<<RW)|(1<<EN);
	LPC_GPIO0->FIODIR |= (1<<D0)|(1<<D1)|(1<<D2)|(1<<D3)|(1<<D4)|(1<<D5)|(1<<D6)|(1<<D7);
	
	/*LCD initialization commands*/
	cmd(0X38); // 8 bit initialization, 2 line 5x7
	cmd(0X80); // Cursor to 1st line
	cmd(0X01); // Clear cursor
	cmd(0X06); // Shift cursor
	cmd(0X0E); // Blink cursor
	
	while(1)
	{
		a=key();
		data(a);
	}		
}
char key()
{
	int e;
	while(1)
	{
		LPC_GPIO1->FIOCLR |= (0XFFu<<24);
		LPC_GPIO1->FIOSET |= (0XF7u<<24);
		_delay();
		e = (LPC_GPIO1->FIOPIN>>24)&0XF0;
		switch(e)
		{
			case 0x70:
				while(!((LPC_GPIO1->FIOPIN>>31)&0X01));
				return('1');
			
			case 0xB0:
				while(!((LPC_GPIO1->FIOPIN>>30)&0X01));
				return('2');
			
			case 0xD0:
				while(!((LPC_GPIO1->FIOPIN>>29)&0X01));
				return('3');
			
			case 0xE0:
				while(!((LPC_GPIO1->FIOPIN>>28)&0X01));
				return('A');
		}
		
		LPC_GPIO1->FIOCLR |= (0XFFu<<24);
		LPC_GPIO1->FIOSET |= (0XFBu<<24);
		_delay();
		e = (LPC_GPIO1->FIOPIN>>24)&0XF0;
		switch(e)
		{
			case 0x70:
				while(!((LPC_GPIO1->FIOPIN>>31)&0X01));
				return('4');
			
			case 0xB0:
				while(!((LPC_GPIO1->FIOPIN>>30)&0X01));
				return('5');
			
			case 0xD0:
				while(!((LPC_GPIO1->FIOPIN>>29)&0X01));
				return('6');
			
			case 0xE0:
				while(!((LPC_GPIO1->FIOPIN>>28)&0X01));
				return('B');
		}
		
		LPC_GPIO1->FIOCLR |= (0XFFu<<24);
		LPC_GPIO1->FIOSET |= (0XFDu<<24);
		_delay();
		e = (LPC_GPIO1->FIOPIN>>24)&0XF0;
		switch(e)
		{
			case 0x70:
				while(!((LPC_GPIO1->FIOPIN>>31)&0X01));
				return('7');
			
			case 0xB0:
				while(!((LPC_GPIO1->FIOPIN>>30)&0X01));
				return('8');
			
			case 0xD0:
				while(!((LPC_GPIO1->FIOPIN>>29)&0X01));
				return('9');
			
			case 0xE0:
				while(!((LPC_GPIO1->FIOPIN>>28)&0X01));
				return('C');
		}
		
		LPC_GPIO1->FIOCLR |= (0XFFu<<24);
		LPC_GPIO1->FIOSET |= (0XFEu<<24);
		_delay();
		e = (LPC_GPIO1->FIOPIN>>24)&0XF0;
		switch(e)
		{
			case 0x70:
				while(!((LPC_GPIO1->FIOPIN>>31)&0X01));
				return('*');
			
			case 0xB0:
				while(!((LPC_GPIO1->FIOPIN>>30)&0X01));
				return('0');
			
			case 0xD0:
				while(!((LPC_GPIO1->FIOPIN>>29)&0X01));
				return('#');
			
			case 0xE0:
				while(!((LPC_GPIO1->FIOPIN>>28)&0X01));
				return('D');
		}
	}
}
		
void cmd(int a)
{
	LPC_GPIO0->FIOCLR |= (1<<D0)|(1<<D1)|(1<<D2)|(1<<D3)|(1<<D4)|(1<<D5)|(1<<D6)|(1<<D7);
	LPC_GPIO1->FIOCLR |= (1<<RS)|(1<<RW)|(1<<EN);
	LPC_GPIO0->FIOSET |= a<<16;
	LPC_GPIO1->FIOSET |= 1<<EN;
	delay();
	LPC_GPIO1->FIOCLR |= 1<<EN;
}

/*Data write function*/
void data(char b)
{
	LPC_GPIO0->FIOCLR |= (1<<D0)|(1<<D1)|(1<<D2)|(1<<D3)|(1<<D4)|(1<<D5)|(1<<D6)|(1<<D7);
	LPC_GPIO1->FIOCLR |= (1<<RS)|(1<<RW)|(1<<EN);
	LPC_GPIO0->FIOSET |= b<<16;
	LPC_GPIO1->FIOCLR |= (1<<RS)|(1<<EN);
	LPC_GPIO1->FIOSET |= (1<<RS)|(1<<EN);
	delay();
	LPC_GPIO1->FIOCLR |= (1<<EN);
}

/*Delay for LCD*/
void delay()
{
	int i,j;
	for(i=0;i<3000;i++)
	{
		for(j=0;j<2000;j++);
	}
}

/*Delay for Keypad*/
void _delay()
{
	int i,j;
	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++);
	}
}
