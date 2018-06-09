#include<avr/io.h>
#include<util/delay.h>
void main()
{
	DDRC=0X00;
	DDRD=0XFF;
	int i;
	while(1)
	{
		if((PINC&0X01)==0)
		{
			PORTD=0XFF;
			_delay_ms(500);
			PORTD=0X00;
			_delay_ms(500);
		}
		else if((PINC&0X02)==0)
		{
			PORTD=0XF0;
			_delay_ms(500);
			PORTD=0X0F;
			_delay_ms(500);
		}
		else if((PINC&0X04)==0)
		{
			PORTD=0XAA;
			_delay_ms(500);
			PORTD=0X55;
			_delay_ms(500);
		}
		else if((PINC&0X08)==0)
		{
			PORTD=0X01;
			_delay_ms(500);
			for(i=0;i<8;i++)
			{
				PORTD=PORTD<<1;
				_delay_ms(500);
			}
		}
		else if((PINC&0X10)==0)
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
				
}

