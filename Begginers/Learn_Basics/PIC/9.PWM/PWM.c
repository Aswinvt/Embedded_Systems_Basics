#include<pic.h>
void delay();
void main()
{
	int i;
	TRISC=0X00;
	CCP2CON=0X0C;
	TMR2ON=1;
	TMR2=0X00;
	while(1)
	{
		for(i=0;i<256;i++)
		{
			CCPR2L=i;
			delay();
		}
	}
}
void delay()
{
	int i,j;
	for(i=0;i<155;i++)
	for(j=0;j<150;j++);
}
