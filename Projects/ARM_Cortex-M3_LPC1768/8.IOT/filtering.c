#include "filtering.h"

char filtering(char f)
{
	char ch;
	ch = UART0_ReadChar();
	if(ch==f)
	{
		ch = UART0_ReadChar();
		return ch;
	}
	return 0;
}
