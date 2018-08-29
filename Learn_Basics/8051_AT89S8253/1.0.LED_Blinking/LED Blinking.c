#include <reg8253.h>

void Delay(int k){
  int j;
  int i;
  for(i=0;i<k;i++){
    for(j=0;j<100;j++);
  }
}

void main (void){
    while(1){                    // infinite loop
            P2 = 0X01;           // LED ON
            Delay(1000);
            P2 = 0X00;           // LED OFF
            Delay(1000);
    }
}