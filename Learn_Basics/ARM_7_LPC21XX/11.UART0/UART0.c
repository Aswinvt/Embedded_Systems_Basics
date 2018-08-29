#include<lpc21xx.h>
void delay();
void trans(char b);
void main()
{
	int i;
	char a[]="HELLO";

	PINSEL0=0x00000001;
 	U0LCR=0X83;
 	U0DLL=0X63;
 	U0DLM=0X00;
 	U0LCR=0X03;
	for(i=0;a[i]!='\0';i++)
	{
		trans(a[i]);
	}
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
	for(i=0;i<255;i++)
	for(j=0;j<250;j++);
}
