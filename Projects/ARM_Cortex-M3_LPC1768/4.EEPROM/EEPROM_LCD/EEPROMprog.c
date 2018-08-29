#include<lpc17xx.h>

#include "stdutils.h"
#include "softi2c.h"
#include "eeprom.h"
#include "gpio.h"
#include "delay.h"

#define RS 18
#define RW 17
#define EN 16

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
	uint8_t a;
	SystemInit();
	
	LPC_GPIO0->FIODIR = (1<<D0)|(1<<D1)|(1<<D2)|(1<<D3)|(1<<D4)|(1<<D5)|(1<<D6)|(1<<D7);
	LPC_GPIO1->FIODIR = (1<<RS)|(1<<RW)|(1<<EN);
	cmd(0X38);
	cmd(0X80);
	cmd(0X01);
	cmd(0X06);
	cmd(0X0E);
	
	EEPROM_Init(AT24C16,P0_27,P0_28);
	
	EEPROM_WriteByte(0XA0, 'A');
	a=EEPROM_ReadByte(0XA0);
	data(a);
	EEPROM_WriteByte(0XA1, 'B');
	a=EEPROM_ReadByte(0XA1);
	data(a);
	EEPROM_WriteByte(0XA2, 'C');
	a=EEPROM_ReadByte(0XA2);
	data(a);
	
//	a=EEPROM_ReadByte(0X00);
//	data(a);
//	a=EEPROM_ReadByte(0X01);
//	data(a);
//	a=EEPROM_ReadByte(0X02);
//	data(a);
//	a=EEPROM_ReadByte(0X03);
//	data(a);
//	a=EEPROM_ReadByte(0X04);
//	data(a);
//	a=EEPROM_ReadByte(0X05);
//	data(a);
//	a=EEPROM_ReadByte(0X06);
//	data(a);
//	a=EEPROM_ReadByte(0X07);
//	data(a);
//	a=EEPROM_ReadByte(0X08);
//	data(a);
//	a=EEPROM_ReadByte(0X09);
//	data(a);
//	a=EEPROM_ReadByte(0X0A);
//	data(a);
}

void cmd(int a)
{
	LPC_GPIO0->FIOCLR= 0XFFFFFFFF;
	LPC_GPIO1->FIOCLR= 0XFFFFFFFF;
	LPC_GPIO0->FIOSET=a<<16;
	LPC_GPIO1->FIOSET= 1<<EN;
	delay();
	LPC_GPIO1->FIOCLR = 1<<EN;
}

void data(char b)
{
	LPC_GPIO0->FIOCLR= 0XFFFFFFFF;
	LPC_GPIO1->FIOCLR= 0XFFFFFFFF;
	LPC_GPIO0->FIOSET=b<<16;
	LPC_GPIO1->FIOCLR= (1<<RS)|(1<<EN);
	LPC_GPIO1->FIOSET= (1<<RS)|(1<<EN);
	delay();
	LPC_GPIO1->FIOCLR = (1<<EN);
}

void delay()
{
	int i,j;
	for(i=0;i<1000;i++)
	{
		for(j=0;j<1000;j++);
	}
}
