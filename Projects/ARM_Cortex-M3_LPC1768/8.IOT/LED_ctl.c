#include "WiFiIOT.h"

void LED_ctrl(char ch)
{
	if(ch=='A')
	{
		UART1_WriteString("\n\rLED1_ON");
		PORT0SET |= (1<<LED1);
	}
	else if (ch=='a')
	{
		UART1_WriteString("\n\rLED1_OFF");
		PORT0CLR |= (1<<LED1);
	}
	else if (ch=='B')
	{
		UART1_WriteString("\n\rLED2_ON");
		PORT0SET |= (1<<LED2);
	}
	else if (ch=='b')
	{
		UART1_WriteString("\n\rLED2_OFF");
		PORT0CLR |= (1<<LED2);
	}
	else if (ch=='C')
	{
		UART1_WriteString("\n\rLED3_ON");
		PORT0SET |= (1<<LED3);
	}
	else if (ch=='c')
	{
		UART1_WriteString("\n\rLED3_OFF");
		PORT0CLR |= (1<<LED3);
	}
	else if (ch=='D')
	{
		UART1_WriteString("\n\rLED4_ON");
		PORT0SET |= (1<<LED4);
	}
	else if (ch=='d')
	{
		UART1_WriteString("\n\rLED4_OFF");
		PORT0CLR |= (1<<LED4);
	}
	else if (ch=='E')
	{
		UART1_WriteString("\n\rLED5_ON");
		PORT0SET |= (1<<LED5);
	}
	else if (ch=='e')
	{
		UART1_WriteString("\n\rLED5_OFF");
		PORT0CLR |= (1<<LED5);
	}
	else if (ch=='F')
	{
		UART1_WriteString("\n\rLED6_ON");
		PORT0SET |= (1<<LED6);
	}
	else if (ch=='f')
	{
		UART1_WriteString("\n\rLED6_OFF");
		PORT0CLR |= (1<<LED6);
	}
	else if (ch=='G')
	{
		UART1_WriteString("\n\rLED7_ON");
		PORT0SET |= (1<<LED7);
	}
	else if (ch=='g')
	{
		UART1_WriteString("\n\rLED7_OFF");
		PORT0CLR |= (1<<LED7);
	}
	else if (ch=='H')
	{
		UART1_WriteString("\n\rLED8_ON");
		PORT0SET |= (1<<LED8);
	}
	else if (ch=='h')
	{
		UART1_WriteString("\n\rLED8_OFF");
		PORT0CLR |= (1<<LED8);
	}
}
