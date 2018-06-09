//Delay program
void delay_msec(int time)
{
 int i=0;
 while(i<time)
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