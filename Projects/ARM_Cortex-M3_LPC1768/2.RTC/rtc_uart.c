#include <lpc17xx.h>
#include "rtc.h"

//RTCTime Time = {Second value,Minute value,Hour value,Day of the month value,Month value,Year value,Day of week value, Day of year value};
//RTCTime Time = {00,30,1,27,10,2017,6,300};

void delay(void);
void UART0_WriteChar(char ch);
void UART0_WriteString(char *str);

int main()
{
	uint32_t Clock_Frequency,Divisor_Latch_Val;
	int hour, min, sec, date, month, year, a, b, c, d;
	SystemInit();
	
	Clock_Frequency = SystemCoreClock/4;
	Divisor_Latch_Val = (Clock_Frequency/(16 * 9600 ));
	
	LPC_SC->PCONP = (1<<3);
	
	LPC_UART0->LCR = (0x03<<0)|(1<<7);
	
	LPC_UART0->DLL = Divisor_Latch_Val & 0xFF;	
	LPC_UART0->DLM = (Divisor_Latch_Val>>8) & 0xFF;
	
	LPC_UART0->FCR = (1<<0)|(1<<1)|(1<<2);
	
	LPC_UART0->LCR &= ~(1<<7);
	
	LPC_PINCON->PINSEL0 &= ~0x000000F0;
  LPC_PINCON->PINSEL0 |= 0x00000050;
	
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
	
		b = ((hour%100)/10)+48;
		UART0_WriteChar(b);
		a = (hour%10)+48;
		UART0_WriteChar(a);
		UART0_WriteChar(':');
		b = ((min%100)/10)+48;
		UART0_WriteChar(b);
		a = (min%10)+48;
		UART0_WriteChar(a);
		UART0_WriteChar(':');
		b = ((sec%100)/10)+48;
		UART0_WriteChar(b);
		a = (sec%10)+48;
		UART0_WriteChar(a);
		UART0_WriteChar(32);
		UART0_WriteChar(32);
		b = ((date%100)/10)+48;
		UART0_WriteChar(b);
		a = (date%10)+48;
		UART0_WriteChar(a);
		UART0_WriteChar('/');
		b = ((month%100)/10)+48;
		UART0_WriteChar(b);
		a = (month%10)+48;
		UART0_WriteChar(a);
		UART0_WriteChar('/');
		d = (year/1000)+48;
		UART0_WriteChar(d);
		c = ((year/100)%10)+48;
		UART0_WriteChar(c);
		b = ((year%1000)/10)+48;
		UART0_WriteChar(b);
		a = (year%10)+48;
		UART0_WriteChar(a);
		UART0_WriteChar(32);
		UART0_WriteChar(32);
		UART0_WriteString("\n\r");
		delay();
	}
}

void delay(void)
{
	int i,j;
	for(i=0;i<2500;i++)
	{
		for(j=0;j<10000;j++);
	}
}

void UART0_WriteChar(char ch)
{
    while(!((LPC_UART0->LSR)&(1<<5)));
    LPC_UART0->THR = ch; 
}

void UART0_WriteString(char *str)
{
	while(*str != '\0')
	{
		UART0_WriteChar(*str);
		str++;
	}
}
