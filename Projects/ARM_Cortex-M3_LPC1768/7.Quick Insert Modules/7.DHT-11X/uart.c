#include <lpc17xx.h>
#include "uart.h"

void UART0_WriteChar(char ch)
{
    while(!((LPC_UART0->LSR)&(1<<5)));
    LPC_UART0->THR = ch; 
}

void UART1_WriteChar(char ch)
{
    while(!((LPC_UART1->LSR)&(1<<5)));
    LPC_UART1->THR = ch; 
}

void UART0_WriteString(char *str)
{
	while(*str != '\0')
	{
		UART0_WriteChar(*str);
		str++;
	}
}

void UART1_WriteString(char *str)
{
	while(*str != '\0')
	{
		UART1_WriteChar(*str);
		str++;
	}
}

void UART0_ReadResponse(void)
{
	char ch;
	while((LPC_UART0->LSR)&(1<<0))
	{
		while(!((LPC_UART0->LSR)&(1<<0)));
		ch = LPC_UART0->RBR;
		UART1_WriteChar(ch);
	}
	LPC_UART0->FCR = (1<<0)|(1<<1)|(1<<2);
}

char UART0_ReadChar(void)
{
    char ch; 
    while(!((LPC_UART0->LSR)&(1<<0)));
		ch = LPC_UART0->RBR;
    return ch;
}
