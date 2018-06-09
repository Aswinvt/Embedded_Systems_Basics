#include<lpc21xx.h>
void delay();
char rec();
void trans(char b);

void main()
{
	int i;
	char a[20];
	PINSEL0=0x00000005;
	U0LCR=0X83;
	U0DLL=0X63;
	U0DLM=0X00;
	U0LCR=0X03;
	while(1)
	{
		while(rec()!='*');
		for(i=0;a[i-1]!='#';i++)
		{
			a[i]=rec();
		}
		a[i-1]='\0';
		for(i=0;a[i]!='\0';i++)
		{
			trans(a[i]);
		}
	}
}

char rec()
{
	while((U0LSR&0X01)==0);
	return(U0RBR);
}

void trans(char b)
{
	U0THR=b;
	while((U0LSR&0X20)==0);
	delay();
}

void delay()
{
	int i,j;
	for(i=0;i<300;i++)
	for(j=0;j<300;j++);
}
