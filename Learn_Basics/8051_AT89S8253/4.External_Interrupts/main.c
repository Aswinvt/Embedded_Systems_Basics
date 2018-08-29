#include <REG8253.H>

void Delay(int k){
  int i, j;
  for(i=0;i<k;i++){
    for(j=0;j<100;j++);
  }
}

void ex0_isr (void) interrupt 0  {  //interrupt subroutine for ext interrupt o
	P0=0xFF;
	Delay(2000);                      //Wait for some time
}

void main (void){
	IT0 = 1;   												// Configure interrupt 0 for falling edge on /INT0 (P3.2)
	EX0 = 1;   												// Enable EX0 Interrupt INT0 (P3.2)
	EA	=	1;   												// Enable Global Interrupt Flag

	while (1){
		P0=0x00;
	}
}
