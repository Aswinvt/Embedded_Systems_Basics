#include<lpc17xx.h>

/*Control ports*/
#define CPS1 24
#define CPS2 25
#define CPS3 26
#define CPS4 27

/*Data ports*/
#define DP1 0
#define DP2 1
#define DP3 2
#define DP4 3
#define DP5 4
#define DP6 5
#define DP7 6
#define DP8 7

/*Register definitions*/
#define IODIRCP LPC_GPIO1->FIODIR
#define IODIRDP LPC_GPIO0->FIODIR
#define IOSETCP LPC_GPIO1->FIOSET
#define IOSETDP LPC_GPIO0->FIOSET
#define IOCLRCP LPC_GPIO1->FIOCLR
#define IOCLRDP LPC_GPIO0->FIOCLR

void delay(void);

int main()
{
	int i;
	char SEG_CODE[10]={0xC0,0xf9,0xA4,0xB0,0x99,0x92,0x82,0xf8,0x80,0x90}; // Common anode - Rev: 1.2
//	char SEG_CODE[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x67}; // Common cathode
	SystemInit();
	
	LPC_GPIO1->FIODIR |= (1<<19); // Accessing USB control pin
	LPC_GPIO1->FIOCLR = (1<<19);
	
	IODIRCP |= (1<<CPS1)|(1<<CPS2)|(1<<CPS3)|(1<<CPS4); // Setting direction for Control port
	IODIRDP |= (1<<DP1)|(1<<DP2)|(1<<DP3)|(1<<DP4)|(1<<DP5)|(1<<DP6)|(1<<DP7)|(1<<DP8); // SEtting direction for Data port
	while(1)
	{
		IOSETCP = (1<<CPS1)|(1<<CPS2)|(1<<CPS3)|(1<<CPS4); // Turn on all Segments
		for(i=0;i<10;i++)
		{
			IOSETDP = (SEG_CODE[i]<<DP1); // Sending Data to Data port
			delay();
			IOCLRDP = (SEG_CODE[i]<<DP1); // Clearing data from Data port
		}
	}
}

void delay()
{
	int i,j;
	for(i=0;i<5000;i++)
	{
		for(j=0;j<3000;j++);
	}
}
