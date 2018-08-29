#include <reg8253.h>

void Delay(int k){
  int i, j;
  for(i=0;i<k;i++){
    for(j=0;j<100;j++);
  }
}

void main (void){
	while(1){
		P3 = 0X01;            // Relay ON
		Delay(1000);
		P3 = 0X00;            // Relay OFF
		Delay(1000);
	}
}
