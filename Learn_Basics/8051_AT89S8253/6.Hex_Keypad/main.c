#include <reg8253.h>

void cmd(int a);
void _data(char b);
void _delay(int k);
char key(void);

void main(){
	char a;
	P0 = 0XF0;										// INITIALIZE P0 4-BIT IN LSB AS OUTPUT AND 4-BIT IN MSB AS INPUT
	cmd(0X38);										// INITIALIZE LCD IN 8 BIT MODE
	cmd(0X01);										// CLEAR DISPLAY REGISTER OF LCD
  cmd(0X80);										// CURSOR POSITION AT STARTING POSITION (LINE1,POSITION1)
  cmd(0X06);										// CURSOR SHIFT
  cmd(0X0E);										// CURSOR BLINK
	while(1){
		a=key();
		_data(a);
	}
}

void cmd(int a){
    P2=a;
    P1=0X01;
    _delay(100);
    P1=0X00;
}

void _data(char b){
    P2=b;
    P1=0X05;
    _delay(10);
    P1=0X04;
}

void _delay(int k){
  int i, j;
  for(i=0;i<k;i++){
    for(j=0;j<100;j++);
  }
}

char key(){
	int e;
	while(1){
		P0=0XF7;												// FOR READING THE FIRST ROW
		_delay(10);
		e=P0&0XF0;
		switch(e){
			
			case 0x70:
				while(!P0_7);
				return('1');
			
			case 0xB0:
				while(!P0_6);
				return('2');
			
			case 0xD0:
				while(!P0_5);
				return('3');
			
			case 0xE0:
				while(!P0_4);
				return('A');
		}
		
		P0=0XFB;												// FOR READING THE SECOND ROW
		_delay(10);											// SET SOME DELAY FOR PORT VALUE
		e=P0&0XF0;
		switch(e){
			
			case 0x70:
				while(!P0_7);								// ELIMINATE DEBOUNCE
				return('4');
			
			case 0xB0:
				while(!P0_6);
				return('5');
			
			case 0xD0:
				while(!P0_5);
				return('6');
			
			case 0xE0:
				while(!P0_4);
				return('B');
		}
		
		P0=0XFD;												// FOR READING THE THIRD ROW
		_delay(10);
		e=P0&0XF0;
		switch(e){
			
			case 0x70:
				while(!P0_7);
				return('7');
			
			case 0xB0:
				while(!P0_6);
				return('8');
			
			case 0xD0:
				while(!P0_5);
				return('9');
			
			case 0xE0:
				while(!P0_4);
				return('C');
		}
		
		P0=0XFE;												// FOR READING THE FOURTH ROW
		_delay(10);
		e=P0&0XF0;
		switch(e){
			
			case 0x70:
				while(!P0_7);
				return('*');
			
			case 0xB0:
				while(!P0_6);
				return('0');
			
			case 0xD0:
				while(!P0_5);
				return('#');
			
			case 0xE0:
				while(!P0_4);
				return('D');
		}
	}
}
