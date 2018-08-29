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
void cmd(int a);
void data(char b);

int main()
{
	SystemInit();
	LPC_GPIO0->FIODIR |= (1<<D0)|(1<<D1)|(1<<D2)|(1<<D3)|(1<<D4)|(1<<D5)|(1<<D6)|(1<<D7); // Setting Pin as output for data port
	LPC_GPIO1->FIODIR |= (1<<RS)|(1<<RW)|(1<<EN); // Setting Pin as Output for Control port
	
	/*LCD initialization commands*/
	cmd(0X38); // 8 bit initialization, 2 line 5x7
	cmd(0X80); // Cursor to 1st line
	cmd(0X01); // Clear cursor
	cmd(0X06); // Shift cursor
	cmd(0X0E); // Blink cursor
	while(1)
	{
		/*Data write*/
		data('H');
		data('E');
		data('L');
		data('L');
		data('O');
		data(' ');
		data('W');
		data('O');
		data('R');
		data('L');
		data('D');
		data('!');
		delay();
		cmd(0X01);
	}
}

/*Command write function*/
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

/*Delay function*/
void delay(void)
{
	int i,j;
	for(i=0;i<500;i++)
	{
		for(j=0;j<3000;j++);
	}
}
