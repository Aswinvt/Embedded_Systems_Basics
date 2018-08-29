#include <REG8253.H>

void timer(unsigned int w);

void main(){
	int width = 50;
	while(1){
		P0 = 0X00;          				// Port0 is used for count reset indication
    P2 = 0XFF;          				// Port2 is used PWM output
		timer(width);								// Delay to control duty cycle of the pulse
		P2 = 0X00;
		timer(width);
		width = width + 50;
		if(width > 500){
			P0 = 0XFF;
			P2 = 0X00;
			timer(1000);
			width = 50;
		}
	}
}

void timer(unsigned int w){ 		// Timer0 to generate a delay.
	int i;
	for(i=0;i<w;i++){							// Loop for repeating the Timer delay for X times
		TMOD = 0x01;								// Set timer0 in mode 1
		TL0 = 0xCB;									// Timer value for 1us delay
		TH0 = 0xFA;
		TR0 = 1;										// Enable Timer 0
		while(!TF0);								// Wait till timer count overflow
		TF0 = 0;										// Reset the overflow flag
		TR0 = 0;										// Disable Timer 0
	}
}