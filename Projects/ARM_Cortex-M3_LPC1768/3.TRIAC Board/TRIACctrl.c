#include<lpc17xx.h>

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

void DELAY_ms(double x);
void DELAY_us(double x);
void trigger(void);

int main()
{
	int CTRL,IN1,IN2,IN3,IN4;
	SystemInit();
	GPIODIR = (0UL<<REF_SQW1)|(0UL<<REF_SQW2)|(0UL<<REF_SQW3)|(0UL<<REF_SQW4)|(1UL<<TRIAC_CTRL1)|(1UL<<TRIAC_CTRL2)|(1UL<<TRIAC_CTRL3)|(1UL<<TRIAC_CTRL4);
	while(1)
	{
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
	DELAY_ms(5);
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
