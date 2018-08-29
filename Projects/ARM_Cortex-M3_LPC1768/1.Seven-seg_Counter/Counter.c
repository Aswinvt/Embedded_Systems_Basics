#include<lpc17xx.h>

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

void DELAY_ms(unsigned int ms_Count);

int main()
{
	int i,cnt,s1,s2,s3,s4,temp,num;
	char SEG_CODE[10]={0xC0,0xf9,0xA4,0xB0,0x99,0x92,0x82,0xf8,0x80,0x90};
	SystemInit();
	IODIRCP = (1<<CPS1)|(1<<CPS2)|(1<<CPS3)|(1<<CPS4);
	IODIRDP = (1<<DP1)|(1<<DP2)|(1<<DP3)|(1<<DP4)|(1<<DP5)|(1<<DP6)|(1<<DP7)|(1<<DP8);
	while(1)
	{
		for(cnt=0;cnt<=9999;cnt++)
		{
			for(i=0; i < 150; i++)
			{
			num = cnt;
      temp = num / 1000;
      num = num % 1000;
      IOSETDP = (SEG_CODE[temp]<<DP1);
			DELAY_ms(1);
      IOSETCP = (1<<CPS4);
      DELAY_ms(1);
			IOCLRCP = (1<<CPS4);
			IOCLRDP = (SEG_CODE[temp]<<DP1);

      temp = num / 100;
      num = num % 100;
      IOSETDP = (SEG_CODE[temp]<<DP1);
			DELAY_ms(1);	
      IOSETCP = (1<<CPS3); 
      DELAY_ms(1);
			IOCLRCP = (1<<CPS3);
			IOCLRDP = (SEG_CODE[temp]<<DP1);

      temp = num / 10;
      IOSETDP = (SEG_CODE[temp]<<DP1);
			DELAY_ms(1);
      IOSETCP = (1<<CPS2); 
      DELAY_ms(1);
			IOCLRCP = (1<<CPS2);
			IOCLRDP = (SEG_CODE[temp]<<DP1);			

      temp = num % 10;
      IOSETDP = (SEG_CODE[temp]<<DP1);
			DELAY_ms(1);
      IOSETCP = (1<<CPS1); 
      DELAY_ms(1);
			IOCLRCP = (1<<CPS1);
			IOCLRDP = (SEG_CODE[temp]<<DP1);
		}
	}
	}
}

void DELAY_ms(unsigned int ms_Count)
{
    unsigned int i,j;
    for(i=0;i<ms_Count;i++)
    {
        for(j=0;j<20000;j++);
    }
}