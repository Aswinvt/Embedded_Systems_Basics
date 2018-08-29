#include <lpc17xx.h>

#define REF_SQW1 24
#define REF_SQW2 25
#define REF_SQW3 26
#define REF_SQW4 27
#define TRIAC_CTRL1 28
#define TRIAC_CTRL2 29
#define TRIAC_CTRL3 30
#define TRIAC_CTRL4 31

#define GPIODIR LPC_GPIO1->FIODIR
#define GPIOSET LPC_GPIO1->FIOSET
#define GPIOCLR LPC_GPIO1->FIOCLR
#define GPIOREAD LPC_GPIO1->FIOPIN

void UART0_WriteChar(char ch);
char UART0_ReadChar(void);
void DELAY_ms(double x);
void DELAY_us(double x);
void trigger(void);
char ch;
int period=4;

int main()
{
	int CTRL,IN1,IN2,IN3,IN4;
	uint32_t Clock_Frequency,Divisor_Latch_Val;
	
	SystemInit();
	
	Clock_Frequency = SystemCoreClock/4;
	Divisor_Latch_Val = (Clock_Frequency/(16 * 9600 ));
	
	LPC_SC->PCONP = (1<<3);
	
	LPC_UART0->LCR = (0x03<<0)|(1<<7);
	
	LPC_UART0->DLL = Divisor_Latch_Val & 0xFF;	
	LPC_UART0->DLM = (Divisor_Latch_Val>>8) & 0xFF;
	
	LPC_UART0->FCR = (1<<0)|(1<<1)|(1<<2);
	
	LPC_UART0->LCR &= ~(1<<7);
	
	LPC_PINCON->PINSEL0 &= ~0x000000F0;
  LPC_PINCON->PINSEL0 |= 0x00000050;
	GPIODIR = (0UL<<REF_SQW1)|(0UL<<REF_SQW2)|(0UL<<REF_SQW3)|(0UL<<REF_SQW4)|(1UL<<TRIAC_CTRL1)|(1UL<<TRIAC_CTRL2)|(1UL<<TRIAC_CTRL3)|(1UL<<TRIAC_CTRL4);

	while(1)
	{
		UART0_WriteChar('A');
		ch = UART0_ReadChar();
		UART0_WriteChar('B');
		period = (int)ch;
		GPIOCLR = (1UL<<TRIAC_CTRL1)|(1UL<<TRIAC_CTRL2)|(1UL<<TRIAC_CTRL3)|(1UL<<TRIAC_CTRL4);
		IN1 = ((GPIOREAD&(1<<REF_SQW1))>>REF_SQW1);
		IN2 = ((GPIOREAD&(1<<REF_SQW2))>>REF_SQW2);
		IN3 = ((GPIOREAD&(1<<REF_SQW3))>>REF_SQW3);
		IN4 = ((GPIOREAD&(1<<REF_SQW4))>>REF_SQW4);
		if(IN1==1|IN2==1|IN3==1|IN4==1)
		{
			CTRL = 1;
		}
		else
		{
			CTRL = 0;
		}
		while(CTRL)
		{
			GPIOCLR = (1UL<<TRIAC_CTRL1)|(1UL<<TRIAC_CTRL2)|(1UL<<TRIAC_CTRL3)|(1UL<<TRIAC_CTRL4);
			trigger();
			GPIOCLR = (1UL<<TRIAC_CTRL1)|(1UL<<TRIAC_CTRL2)|(1UL<<TRIAC_CTRL3)|(1UL<<TRIAC_CTRL4);
			CTRL = 0;
		}
		while(!CTRL)
		{
			GPIOCLR = (1UL<<TRIAC_CTRL1)|(1UL<<TRIAC_CTRL2)|(1UL<<TRIAC_CTRL3)|(1UL<<TRIAC_CTRL4);
			trigger();
			GPIOCLR = (1UL<<TRIAC_CTRL1)|(1UL<<TRIAC_CTRL2)|(1UL<<TRIAC_CTRL3)|(1UL<<TRIAC_CTRL4);
			CTRL = 1;
		}
		GPIOCLR = (1UL<<TRIAC_CTRL1)|(1UL<<TRIAC_CTRL2)|(1UL<<TRIAC_CTRL3)|(1UL<<TRIAC_CTRL4);
	}
}

void trigger()
{
	DELAY_ms(8);
	GPIOSET = (1UL<<TRIAC_CTRL1)|(1UL<<TRIAC_CTRL2)|(1UL<<TRIAC_CTRL3)|(1UL<<TRIAC_CTRL4);
	DELAY_us(10);
	GPIOCLR = (1UL<<TRIAC_CTRL1)|(1UL<<TRIAC_CTRL2)|(1UL<<TRIAC_CTRL3)|(1UL<<TRIAC_CTRL4);
}

void DELAY_ms(double x)
{
	unsigned int pclk, PreScale, ReqCntsPerSec;
	uint8_t interrupt_bit;
	
	LPC_SC->PCONP |= (1<<1);
	LPC_TIM0->MCR = (1<<0)|(1<<1);
	
	LPC_TIM0->MR0 = x*1000;
	
	pclk = SystemCoreClock/4;		
	
	ReqCntsPerSec	= 1000000;
	
	PreScale = pclk/ReqCntsPerSec;
	LPC_TIM0->PR = PreScale - 1;
	
	LPC_TIM0->TCR = (1<<0);
	
	while(LPC_TIM0->IR!=1);
	interrupt_bit = LPC_TIM0->IR;
  LPC_TIM0->IR = interrupt_bit;
}

void DELAY_us(double x)
{
	unsigned int pclk, PreScale, ReqCntsPerSec;
	uint8_t interrupt_bit;
	
	LPC_SC->PCONP |= (1<<1);
	LPC_TIM0->MCR = (1<<0)|(1<<1);
	
	LPC_TIM0->MR0 = x;
	
	pclk = SystemCoreClock/4;		
	
	ReqCntsPerSec	= 1000000;
	
	PreScale = pclk/ReqCntsPerSec;
	LPC_TIM0->PR = PreScale - 1;
	
	LPC_TIM0->TCR = (1<<0);
	
	while(LPC_TIM0->IR!=1);
	interrupt_bit = LPC_TIM0->IR;
  LPC_TIM0->IR = interrupt_bit;
}

void UART0_WriteChar(char ch)
{
    while(!((LPC_UART0->LSR)&(1<<5)));
    LPC_UART0->THR = ch; 
}

char UART0_ReadChar()
{
	uint8_t retry;
	char ch; 
	while(!((LPC_UART0->LSR)&(1<<0)))
		if(retry++ > 0xFE) return 0;
	ch = LPC_UART0->RBR;
	return ch;
}
