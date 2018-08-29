#include<lpc17xx.h>
#include<stdint.h>

void UART0_WriteChar(char ch);
void UART0_WriteString(char *str);
char UART0_ReadChar(void);
void UART1_WriteChar(char ch);
void UART1_WriteString(char *str);
char UART1_ReadChar(void);
void delay(void);

int main()
{
	char ch0;
	uint32_t Clock_Frequency0,Divisor_Latch_Val0,Clock_Frequency1,Divisor_Latch_Val1;
	
	SystemInit();
	
	Clock_Frequency0 = SystemCoreClock/4;
	Divisor_Latch_Val0 = (Clock_Frequency0/(16 * 9600 ));
	Clock_Frequency1 = SystemCoreClock/4;
	Divisor_Latch_Val1 = (Clock_Frequency1/(16 * 9600 ));
	
	LPC_SC->PCONP = (1<<3)|(1<<4);
	
	LPC_UART0->LCR = (0x03<<0)|(1<<7);
	LPC_UART1->LCR = (0x03<<0)|(1<<7);
	
	LPC_UART0->DLL = Divisor_Latch_Val0 & 0xFF;	
	LPC_UART0->DLM = (Divisor_Latch_Val0>>8) & 0xFF;
	LPC_UART1->DLL = Divisor_Latch_Val1 & 0xFF;	
	LPC_UART1->DLM = (Divisor_Latch_Val1>>8) & 0xFF;
	
	LPC_UART0->LCR &= ~(1<<7);
	LPC_UART1->LCR &= ~(1<<7);
	
	LPC_UART0->FCR = (1<<0)|(1<<1)|(1<<2);
	LPC_UART1->FCR = (1<<0)|(1<<1)|(1<<2);
	
	LPC_PINCON->PINSEL0 &= ~0xF00000F0;
  LPC_PINCON->PINSEL0 |= 0x40000050;
	LPC_PINCON->PINSEL4 &= ~0x000000F;
  LPC_PINCON->PINSEL4 |= 0x0000000A;
	
	UART0_WriteString("AT");
	UART0_WriteChar(0X0D);
	delay();
//	ATreceive();
//	UART0_WriteString("AT+CSCA?");
//	UART0_WriteChar(0X0D);
//	ATreceive();
//	UART0_WriteString("AT+CMGF=1");
//	UART0_WriteChar(0X0D);
//	ATreceive();
//	UART0_WriteString("AT+CMGS=\"+917736439027\"");
//	UART0_WriteChar(0X0D);
//	ATreceive();
//	UART0_WriteString("VEHICLE STARTED\x1A");
//	UART0_WriteChar(0X0D);
//	ATreceive();

	while(1)
	{
		ch0 = UART0_ReadChar(); 
		UART0_WriteChar(ch0);
	} 
}

void UART0_WriteChar(char ch)
{
    while(!((LPC_UART0->LSR)&(1<<5)));
    LPC_UART0->THR = ch; 
}

void UART1_WriteChar(char ch)
{
    while(!((LPC_UART1->LSR)&(1<<5)));
    LPC_UART1->THR = ch; 
}

void UART0_WriteString(char *str)
{
	while(*str != '\0')
	{
		UART0_WriteChar(*str);
		str++;
	}
}

void UART1_WriteString(char *str)
{
	while(*str != '\0')
	{
		UART1_WriteChar(*str);
		str++;
	}
}

char UART0_ReadChar(void)
{
    char ch;
		while(!((LPC_UART0->LSR)&(1<<0)));
		ch = LPC_UART0->RBR;
    return ch;
}

char UART1_ReadChar(void)
{
    char ch; 
    while(!((LPC_UART1->LSR)&(1<<0)));
		ch = LPC_UART1->RBR;
    return ch;
}

void delay(void)
{
	int i,j;
	for(i=0;i<500;i++)
	{
		for(j=0;j<500;j++);
	}
}
