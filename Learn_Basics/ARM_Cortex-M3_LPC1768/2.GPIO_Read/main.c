#include <lpc17xx.h>

#define IN 16 //Input Pin
#define LED 17 //Output Pin

int main(){
	SystemInit();
	LPC_GPIO0->FIODIR |= (0<<IN)|(1<<LED); //Setting Direction for pins
	while(1){
		if((LPC_GPIO0->FIOPIN >> IN)&0X01){ // Read bit
			LPC_GPIO0->FIOCLR |= (1<<LED); // Clear bit
		}
		else{
			LPC_GPIO0->FIOSET |= (1<<LED); // Set bit
		}
	}
}
