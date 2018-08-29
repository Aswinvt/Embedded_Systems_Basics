#include <REG8253.H>

/* uart initialisation function */
void UART_init()
{
	SCON=0x50;            									// Configure serial control register
	PCON=0x80;            									// SMOD bit set
  TMOD=0x20;           										// Using timer1,8-bit reload mode for baudrate generation
	TH1=0xF7;            										// 9600 baudrate(16 mhz clock)
	TR1=1;               										// Start timer
}

/* function to receive a character in uart */    
unsigned char Uart_read_char(){
	unsigned char character;
	while(!RI);               							// Wait until character received completely
	character=SBUF;           							// Read the character from buffer reg
	RI=0;                     							// Clear the flag
	return character;         							// Return the received character
}

/* function to transmit a character in uart */
void Uart_write_char(unsigned char character){
	SBUF=character;          								// Load the character to be transmitted in to the buffer reg
	while(!TI);              								// Wait until transmission complete
	TI=0;                    								// Clear flag
}

void main(){
	unsigned char received;     
	UART_init();
	Uart_write_char('H');										// Write a user defined character
	Uart_write_char('E');
	Uart_write_char('L');
	Uart_write_char('L');
	Uart_write_char('O');
	Uart_write_char(0X0D);									// For Enter new line
	while(1){
		received=Uart_read_char();            // Receive character
		Uart_write_char(received);            // Transmit the received character.
	}
}
