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

char UART0_ReadChar(void)
{
    char ch; 
    while(!((LPC_UART0->LSR)&(1<<0)));
		ch = LPC_UART0->RBR;
    return ch;
}

char UART1_ReadChar(void)
{
    char ch; 
    while(!((LPC_UART1->LSR)&(1<<0)));
		ch = LPC_UART1->RBR;
    return ch;
}
