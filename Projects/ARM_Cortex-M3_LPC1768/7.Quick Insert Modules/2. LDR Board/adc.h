#include <lpc17xx.h>
#include "delay_ms.h"
#include "uart.h"
#include "uart_int.h"
#include "split.h"

#define		AD0_0			14
#define   AD_1			16
#define   AD_2			18
#define   AD_3			20

#define 	ADCR_SEL0				0
#define 	ADCR_SEL1				1
#define 	ADCR_SEL2				2
#define 	ADCR_SEL3				3
#define 	ADCR_SEL4				4
#define 	ADCR_SEL5				5
#define 	ADCR_SEL6				6
#define 	ADCR_SEL7				7

#define		ADCR_CLKDIV			8
#define		ADCR_BURST		 16
#define		ADCR_PDN			 21
#define		ADCR_START		 24
#define		ADCR_EDGE			 27

#define ADC_OFFSET			(1U<<4)
#define ADC_RESULT				4		
#define ADC_DONE				(1U<<31)
#define ADC_OVERRUN			(1U<<30)

void adc_int(int ADC_PIN);
