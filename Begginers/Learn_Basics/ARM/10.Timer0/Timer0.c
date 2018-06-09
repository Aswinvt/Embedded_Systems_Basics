#include<lpc21xx.h>
void timer();

void main()
{
	IO0DIR=0XFFFFFFFF;
	T0TCR=0X01;
	T0TC=0X00000000;
	T0PR=0X00000005;
	T0PC=0X00000000;
	T0MR0=0X000FFFF;
	T0MCR=0X00000003;   
	while(1)
  	{
  		IO0SET=0XFFFFFFFF;
  		timer();
  		IO0CLR=0XFFFFFFFF;
  		timer();
  	}

}
void timer()
{
	while((T0IR&0X01)==0);
	T1IR=0X00;
}   
                                                                     