#include<avr/io.h>
#include<util/delay.h>
void main()
{
	int i;
	DDRB=0XFF;
	TCCR0=0X69;
	TCNT0=0X00;
	while(1)
	{
		for(i=0;i<256;i++)
		{
			OCR0=i;
			_delay_ms(500);
		}
	}
}
