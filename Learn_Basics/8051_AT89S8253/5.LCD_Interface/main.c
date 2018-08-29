#include <reg8253.h>

void cmd(int a);
void _data(char b);
void display(const char *p);
void _delay(int k);

void main(){
    cmd(0X38);             // Initialize LCD in 8-bit mode
    cmd(0X01);             // Clear LCD display register
    cmd(0X80);             // Move curser to 0th position of Line 1
    cmd(0X06);             // Curser Shift
    cmd(0X0E);             // Curser Blink
    _data('H');
    _data('E');
    _data('L');
    _data('L');
    _data('O');
}

void cmd(int a){
    P2=a;										// Load data on the data port.
    P1=0X01;								// Set RS pin and R/W pin as LOW and Set enable pin HIGH 
    _delay(500);
    P1=0X00;								// Set enable pin LOW
}

void _data(char b){
    P2=b;										// Load data on the data port.
    P1=0X05;								// Set R/W pin as LOW and Set RS pin as HIGH and Set enable pin HIGH 
    _delay(500);
    P1=0X04;								// Set enable pin LOW
}

void _delay(int k){
  int j;
  int i;
  for(i=0;i<k;i++){
    for(j=0;j<100;j++);
  }
}
