#include <REG8253.H>

void timer(unsigned int d);

void main(){
	while(1){
    P2 = 0XFF;          				// Port2 is turned ON
		timer(1000);								// Delay of 1 sec using Timer
		P2 = 0X00;									// Port2 is turned ON
		timer(1000);								// Delay of 1 sec using Timer
	}
}

void timer(unsigned int d){ 		// Timer0 to generate a delay.
	int i;
	for(i=0;i<d;i++){							// Loop for repeating the Timer delay for X times
		TMOD = 0x01;								// Set timer0 in mode 1
		TL0 = 0xCB;									// Timer value for 1us delay
		TH0 = 0xFA;
		TR0 = 1;										// Enable Timer 0
		while(!TF0);								// Wait till timer count overflow
		TF0 = 0;										// Reset the overflow flag
		TR0 = 0;										// Disable Timer 0
	}
}