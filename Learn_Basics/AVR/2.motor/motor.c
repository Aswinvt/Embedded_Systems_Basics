#include<avr/io.h>
void main()
{
	DDRB=0XFF;
	while(1)
	{
		PORTB=0X2D;
	}
}
