#include <lpc17xx.h>
#include "delay.h"

#define CPS1 24
#define CPS2 25
#define CPS3 26
#define CPS4 27

#define DP1 0
#define DP2 1
#define DP3 2
#define DP4 3
#define DP5 4
#define DP6 5
#define DP7 6
#define DP8 7

#define IODIRCP LPC_GPIO1->FIODIR
#define IODIRDP LPC_GPIO0->FIODIR
#define IOSETCP LPC_GPIO1->FIOSET
#define IOSETDP LPC_GPIO0->FIOSET
#define IOCLRCP LPC_GPIO1->FIOCLR
#define IOCLRDP LPC_GPIO0->FIOCLR

int main()
{
	int i,cnt,temp,num;
	char SEG_CODE[10]={0xC0,0xf9,0xA4,0xB0,0x99,0x92,0x82,0xf8,0x80,0x90}; // Rev: 1.2
//	char SEG_CODE[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x67};
	SystemInit();
	
	LPC_GPIO1->FIODIR |= (1<<19); // Accessing USB control pin
	LPC_GPIO1->FIOCLR = (1<<19);
	
	IODIRCP = (1<<CPS1)|(1<<CPS2)|(1<<CPS3)|(1<<CPS4);
	IODIRDP = (1<<DP1)|(1<<DP2)|(1<<DP3)|(1<<DP4)|(1<<DP5)|(1<<DP6)|(1<<DP7)|(1<<DP8);
	while(1)
	{
		for(cnt=0;cnt<=9999;cnt++)
		{
			for(i=0; i < 50; i++)
			{
				num = cnt;
				temp = num / 1000;
				num = num % 1000;
				IOSETDP = (SEG_CODE[temp]<<DP1);
				DELAY_ms(2);
				IOSETCP = (1<<CPS4);
				DELAY_ms(2);
				IOCLRCP = (1<<CPS4);
				IOCLRDP = (SEG_CODE[temp]<<DP1);

				temp = num / 100;
				num = num % 100;
				IOSETDP = (SEG_CODE[temp]<<DP1);
				DELAY_ms(2);
				IOSETCP = (1<<CPS3); 
				DELAY_ms(2);
				IOCLRCP = (1<<CPS3);
				IOCLRDP = (SEG_CODE[temp]<<DP1);

				temp = num / 10;
				IOSETDP = (SEG_CODE[temp]<<DP1);
				DELAY_ms(2);
				IOSETCP = (1<<CPS2); 
				DELAY_ms(2);
				IOCLRCP = (1<<CPS2);
				IOCLRDP = (SEG_CODE[temp]<<DP1);			

				temp = num % 10;
				IOSETDP = (SEG_CODE[temp]<<DP1);
				DELAY_ms(2);
				IOSETCP = (1<<CPS1); 
				DELAY_ms(2);
				IOCLRCP = (1<<CPS1);
				IOCLRDP = (SEG_CODE[temp]<<DP1);
			}
		}
	}
}


