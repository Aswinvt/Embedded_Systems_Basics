#include "WiFiIOT.h"

int main()
{
	char ch;
	SystemInit();	
	uart_int();
	PORT0DIR |= (1<<LED1)|(1<<LED2)|(1<<LED3)|(1<<LED4)|(1<<LED5)|(1<<LED6)|(1<<LED7)|(1<<LED8);
	UART0_WriteString("AT\r\n");
	UART1_WriteString("\r\nWRITING COMMAND \"AT\"\r\n");
	UART0_ReadResponse();
	UART0_WriteString("AT+CWMODE=3\r\n");													// SoftAP+Station mode
	UART1_WriteString("\r\nWRITING COMMAND \"AT+CWMODE=3\"\r\n");
	UART0_ReadResponse();
	UART0_WriteString("AT+CIPMUX=1\r\n");
	UART1_WriteString("\r\nWRITING COMMAND \"AT+CIPMUX=1\"\r\n");
	UART0_ReadResponse();
	UART0_WriteString("AT+CIPSERVER=1,80\r\n"); 									//Set up a TCP server
	UART1_WriteString("\r\nWRITING COMMAND AT+CIPSERVER=1\r\n");
	UART0_ReadResponse();

	while(1)
	{
		ch = filtering(':');
		LED_ctrl(ch);
	}
}
