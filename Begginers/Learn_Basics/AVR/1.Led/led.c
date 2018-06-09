#include<avr/io.h>
#include<util/delay.h>
void main()
{
	DDRD=0XFF;
	while(1)
	{
		PORTD=0XFF;
		_delay_ms(1000);
		PORTD=0X00;
		_delay_ms(1000);
	}
}
