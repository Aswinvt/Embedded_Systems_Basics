#include<pic.h>
char rec();
void trans(char a);
void main()
{
	int i;
	char a[10];
	TRISC=0X80;
	TXSTA=0X24;
	RCSTA=0X90;
	SPBRG=129;
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
void trans(char a)
{
	TXREG=a;
	while(TXIF==0);
	TXIF=0;
}
char rec()
{
	while(RCIF==0);
	return(RCREG);
}