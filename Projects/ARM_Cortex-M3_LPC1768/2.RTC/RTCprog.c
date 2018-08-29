#include <lpc17xx.h>
#include "rtc.h"

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

//RTCTime Time = {Second value, Minute value, Hour value, Day of the month value, Month value, Year value, Day of week value, Day of year value};
//RTCTime Time = {00,30,11,18,06,2018,2,169}; //Uncomment to set time

void delay(void);
void cmd(int a);
void data(char b);

int main()
{
	int hour, min, sec, date, month, year, a, b, c, d;
	
	SystemInit();
	
	LPC_GPIO0->FIODIR = (1<<D0)|(1<<D1)|(1<<D2)|(1<<D3)|(1<<D4)|(1<<D5)|(1<<D6)|(1<<D7);
	LPC_GPIO1->FIODIR = (1<<RS)|(1<<RW)|(1<<EN);
	cmd(0X38);
	cmd(0X80);
	cmd(0X01);
	cmd(0X0C);
	
	RTC_CTCReset();
	LPC_RTC->CCR = (1<<4);
	LPC_RTC->CALIBRATION = 0x00;
	RTCStart();
	
//	RTCSetTime(Time);
	
	while(1)
	{
		hour = LPC_RTC->HOUR;
		min  = LPC_RTC->MIN; 
		sec  = LPC_RTC->SEC;
		
		date  = LPC_RTC->DOM;   
		month = LPC_RTC->MONTH;  
		year  = LPC_RTC->YEAR;
	
		cmd(0X84);
		b = ((hour%100)/10)+48;
		data(b);
		a = (hour%10)+48;
		data(a);
		data(':');
		b = ((min%100)/10)+48;
		data(b);
		a = (min%10)+48;
		data(a);
		data(':');
		b = ((sec%100)/10)+48;
		data(b);
		a = (sec%10)+48;
		data(a);
		cmd(0XC3);
		b = ((date%100)/10)+48;
		data(b);
		a = (date%10)+48;
		data(a);
		data('/');
		b = ((month%100)/10)+48;
		data(b);
		a = (month%10)+48;
		data(a);
		data('/');
		d = (year/1000)+48;
		data(d);
		c = ((year/100)%10)+48;
		data(c);
		b = ((year%1000)/10)+48;
		data(b);
		a = (year%10)+48;
		data(a);
	}
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
		for(j=0;j<100;j++);
	}
}
