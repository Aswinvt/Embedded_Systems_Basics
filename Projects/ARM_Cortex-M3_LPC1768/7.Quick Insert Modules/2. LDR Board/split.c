#include "uart.h"
#include "split.h"

void split(unsigned char s)
{
	unsigned char a[4];
	int x=0;

	while(x<4){
		a[x] = s%10;
		s = s/10;
		x++;
	}
	
	do
	{
		--x;
		UART0_WriteChar(a[x]+48);
	}while(x);
}
