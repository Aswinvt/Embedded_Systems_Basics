#include<avr/io.h>
#include<util/delay.h>
void main()
{
	int i;
	DDRD=0XFF;
	while(1)
	{
		PORTD=0X80;
		_delay_ms(500);
		for(i=0;i<8;i++)
		{
			PORTD=PORTD>>1;
			_delay_ms(500);
		}
	}
}


