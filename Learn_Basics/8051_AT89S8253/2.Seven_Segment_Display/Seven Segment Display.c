#include <reg8253.h>

void Delay(int k){
  int j;
  int i;
  for(i=0;i<k;i++){
    for(j=0;j<100;j++);
  }
}

void main (void){
	int i;												 /*{	0,	1,	 2,		3,	 4,		5,	 6,		7,	 8,		9	 } SEGMENT CODE FOR COMMON ANODE*/
	unsigned char const SEG_CODE[] = {0xC0,0xf9,0xA4,0xB0,0x99,0x92,0x82,0xf8,0x80,0x90};
	while(1){											 // infinite loop
		P1 = 0X0F;									 // Control port
		for(i=0; i<10; i++){
			P2 = SEG_CODE[i];					 // Data port
			Delay(1000);
		}
	}
}
