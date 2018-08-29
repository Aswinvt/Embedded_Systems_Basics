/*
 * File name            : main.c
 * Compiler             : MDK-Lite
 * IDE                  : Keil uVision V5
 * Author               : Etiq Technologies
 * Processor            : LPC1768
 * Created on           : November 20, 2017, 01:20 PM
 * Description          : Program for UART initialization
 */
 
#include <lpc17xx.h>
#include "uart_int.h"

void uart_int(int BR)
{
	uint32_t Clock_Frequency0,Divisor_Latch_Val0,Clock_Frequency1,Divisor_Latch_Val1;
	
	SystemInit();
	
	Clock_Frequency0 = SystemCoreClock/4;
	Divisor_Latch_Val0 = (Clock_Frequency0/(16 * BR ));
	Clock_Frequency1 = SystemCoreClock/4;
	Divisor_Latch_Val1 = (Clock_Frequency1/(16 * BR ));
	
	LPC_SC->PCONP |= (1<<3)|(1<<4);
	
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
	
	LPC_PINCON->PINSEL0 &= ~0x000000F0;
  LPC_PINCON->PINSEL0 |= 0x00000050;
	LPC_PINCON->PINSEL4 &= ~0x000000F;
  LPC_PINCON->PINSEL4 |= 0x0000000A;
}
