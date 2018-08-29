#include<lpc17xx.h>
void delay_ms(double x);

int main()
{
	int D_Cycle;
	SystemInit();
	LPC_PINCON->PINSEL3 &= ~(3<<4); //Clear bits
	LPC_PINCON->PINSEL3 |=(2<<4); //Configure PWM1.1 (P1.18)
	LPC_PWM1->MCR = (1<<1);
	LPC_PWM1->MR0 = 100;
	LPC_PWM1->LER = (1<<0);
	LPC_PWM1->TCR &= 0x0000000F;
	LPC_PWM1->TCR |=((1<<3)|(1<<0));
	LPC_PWM1->PR =0X00;
	LPC_PWM1->PCR =(1<<9);
 while(1)
 {
			for(D_Cycle=0; D_Cycle<100; D_Cycle++)
        {
            LPC_PWM1->MR1	 = D_Cycle;
						LPC_PWM1->LER = (1<<1); 
            delay_ms(5);
        }

        for(D_Cycle=99; D_Cycle>1; D_Cycle--)
        {
				LPC_PWM1->MR1 = D_Cycle;
					LPC_PWM1->LER = (1<<1);
            delay_ms(5);
        }
    }
}
void delay_ms(double x)
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
