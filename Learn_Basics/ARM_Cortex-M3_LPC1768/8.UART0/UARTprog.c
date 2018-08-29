#include<lpc17xx.h>

void UART0_WriteChar(char ch);

char UART0_ReadChar(void);

int main()
{
	uint32_t Clock_Frequency, Divisor_Latch_Val;
	char ch;
	SystemInit();
	
	LPC_SC->PCONP |= (1<<3); // Configure power for UART module
	
	LPC_UART0->LCR &= ~(0x03<<0); // Clearing bits
	LPC_UART0->LCR |= (0x03<<0); // Configuring the word length for 8-bit mode
	
	LPC_UART0->LCR &= ~(1<<7); // Clearing bits
	LPC_UART0->LCR |= (1<<7); // Configuring the Divisor latch register access
	
	/*Baud Rate Calculation*/
	Clock_Frequency = SystemCoreClock/4;
	Divisor_Latch_Val = (Clock_Frequency/(16 * 9600 ));
	
	LPC_UART0->DLL = Divisor_Latch_Val & 0xFF;	// Setting DLL value for Baud Rate
	LPC_UART0->DLM = (Divisor_Latch_Val>>8) & 0xFF;
	
	LPC_UART0->LCR &= ~(1<<7); // Disable divisor latch register access
	
	LPC_UART0->FCR &= ~((1<<0)|(1<<1)|(1<<2)); // Clearing bits
	LPC_UART0->FCR |= (1<<0)|(1<<1)|(1<<2); // Configuring FIFO
	
	LPC_PINCON->PINSEL0 &= ~(0XF<<4); // Clearing bits
  LPC_PINCON->PINSEL0 |= (0x5<<4); // Configuring P0.2 & P0.3 as RX and TX pin for UART0
	
	UART0_WriteChar('U'); 
	UART0_WriteChar('A');
	UART0_WriteChar('R');
	UART0_WriteChar('T');
	UART0_WriteChar('0');
	
	while(1)
		{
			ch = UART0_ReadChar(); 
			UART0_WriteChar(ch);
		} 
}

void UART0_WriteChar(char ch)
{
    while(!((LPC_UART0->LSR)&(1<<5))); // Line status register
    LPC_UART0->THR = ch; // Transmitter Buffer
}

char UART0_ReadChar(void)
{
    char ch; 
    while(!((LPC_UART0->LSR)&(1<<0))); // Line status register
		ch = LPC_UART0->RBR; // Receiver Buffer
    return ch;
}
