#include<pic.h>
void trans(char);
void delay();
void main()
{
	int i;
	char a[]="SMEC";
	TRISC=0X80;
	TXSTA=0X24;
	RCSTA=0X90;
	SPBRG=129;
	for(i=0;a[i]!='\0';i++)
	{
		trans(a[i]);
	}
	while(1);
}

void trans(char a)
{
	TXREG=a;
	while(TXIF==0);
	TXIF=0;
}

