#include "delay.h"

void DELAY_us(unsigned int count)
{
  unsigned int j=0,i=0;

  for(j=0;j<count;j++)
  {
    for(i=0;i<23;i++);
  }
}

void DELAY_ms(unsigned int count)
{
	unsigned int i;
	for (i=0;i<count;i++)
	{
		DELAY_us(1000);
	}
}

void DELAY_sec(unsigned int count)
{
	unsigned int i;
	for (i=0;i<count;i++)
	{
		DELAY_ms(1000);
	}
}
