//Program to make an automatic room light and bidirectional visitor counter using IR sensor	an AT89S52 microcontroller.
#include <reg51.h>
sbit up=P1^0;  //up pin to make counter count up.
sbit down=P1^1;  //down pin to make counter count down.
sbit relay = P1^4; //pin to make swithch on and off light relay.
sbit dig_ctrl_1=P1^2;  //declare the control pins of seven segments.
sbit dig_ctrl_2=P1^3;


unsigned char dig_val[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x67};
unsigned int dig_1=0,dig_2=0,count=0,temp=0;


void delay(int x)
{
  int i=0;
  while(i<x)
  {
    TMOD=0x10;
    TH1=0xFC;
    TL1=0x66;
    TR1=1;
    while(TF1==0);
    TR1=0;
    TF1=0;
    i++;
  }
}


void init()  // to initialize the input, output pins and Timer0
{
  up=down=0;
  relay=0;
  dig_ctrl_1=1;
  dig_ctrl_2=1;
  P2=0x3F;
  P3=0x3F;
  TMOD=0x01;
  TL0=0xF6;
  TH0=0xFF;
  IE=0x82;
  TR0=1;
}

void main()
{
  init();
  while(1)
  {
   if(up==1)
   {
	 while(!down)
     {
     }
   	 if(count<99)
	 {
	   count++;
	 }
	 temp=count;
	 dig_1=temp%10;
	 temp=temp/10;
     dig_2=temp%10;
     relay = 1;
	 P2=dig_val[dig_1];
	 if(count>9)
	 {
	 P3=dig_val[dig_2];
	 }
	 else
	 P3=0x3F;
	 delay(1000);
   }
   if(down==1)
   {
     while(!up)
     {
	 }
	 if(count>0)
	 {
	   count--;
	 }
 	 temp=count; 	 
	 dig_1=temp%10;
	 temp=temp/10;
	 dig_2=temp%10;
     if(count==0)
     { 
	   relay=0;
     }
	 P2=dig_val[dig_1];
	 if(count>9)
	 {
	 P3=dig_val[dig_2];
	 }
	 else
	 P3=0x3F;
	 delay(1000);
   }
  }
}