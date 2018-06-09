#include<pic.h>
void delay();
void interrupt isr(void);
void main()
{
	TRISB=0X01;
	PORTB=0X00;
	TRISD=0X00;
	PORTD=0X00;
	INTEDG=0;
	GIE=1;
	PEIE=1;
	INTE=1;
	while(1);
}
void interrupt isr(void)
{
	if(INTF==1)
	{
		PORTD=0XFF;
		delay();
		PORTD=0X00;
		delay();
	}
	INTF=0;
}
void delay()
{
	int i,j;
	for(i=0;i<355;i++)
	for(j=0;j<350;j++);
}