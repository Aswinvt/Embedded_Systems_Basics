//Program for automatic light
#include<reg51.h>
#include<delay.h>

sbit in=P1^0; //In count pin
sbit out=P1^1; //Out count pin
sbit RELAY=P2^7; //Output pin for on and off

void main()
{
 int count=0;
 in=out=0;
 RELAY=0;

 while(1)
 {
 if(in==1)
 {
  while(!out)
  {
  }
  count++;
  RELAY=1;
  delay_msec(1000);
 }
 if(out==1&&count)
 {
  while(!in)
  {
  }
  count--;
  delay_msec(1000);
  if(!count)
  RELAY=0;
  }
 }
} 