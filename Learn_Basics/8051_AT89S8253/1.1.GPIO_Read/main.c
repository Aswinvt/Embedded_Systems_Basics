#include <REG8253.H>

void Delay(int k){
  int i,j;
  for(i=0;i<k;i++){
    for(j=0;j<100;j++);
  }
}

void main(){
    while(1){
        P2_0 = 1;            	//Port2 0th pin is made an input port
        if(P2_0 == 0){
            P0 = 0x00;        //Blinks the LEDs connected to the Port0 with a delay
            Delay(250);
            P0 = 0xFF;
            Delay(250);
        }
    }
}
