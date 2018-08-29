/*
 * File name            : main.c
 * Compiler             : MDK-Lite
 * IDE                  : Keil uVision V5
 * Author               : Etiq Technologies
 * Processor            : LPC1768
 * Description          : Program for GPIO
 */
 
#include "gpio.h"

void GPIO_SetPinDir( uint8_t uipinnum, uint8_t uidirection )
{
	uint8_t uiportnum;
	LPC_GPIO_TypeDef *GPIO_FIO_DIR;
	
	uiportnum = uipinnum >> 5;
	uipinnum = uipinnum & 0x1F;
	
	GPIO_FIO_DIR = (LPC_GPIO_TypeDef *) (LPC_GPIO_BASE + (uiportnum << 5));
	
	if(uidirection == INPUT)
		GPIO_FIO_DIR->FIODIR |= (0 << uipinnum);
	
	else if(uidirection == OUTPUT)
		GPIO_FIO_DIR->FIODIR |= (1 << uipinnum);

}

void GPIO_SetPinVal( uint8_t uipinnum , uint8_t uipinval)
{
	uint8_t uiportnum;
	LPC_GPIO_TypeDef *GPIO_FIO_SET;
	
	uiportnum = uipinnum >> 5;
	uipinnum = uipinnum & 0x1F;

	GPIO_FIO_SET = (LPC_GPIO_TypeDef *) (LPC_GPIO_BASE + (uiportnum << 5));

	GPIO_FIO_SET->FIOCLR |= (1 << uipinnum);	
	GPIO_FIO_SET->FIOSET |= (uipinval << uipinnum);	
}

uint8_t GPIO_GetPinVal( uint8_t uipinnum )
{
	uint8_t uiportnum;
	LPC_GPIO_TypeDef *GPIO_FIO_GET;
	
	uiportnum = uipinnum >> 5;
	uipinnum = uipinnum & 0x1F;

	GPIO_FIO_GET = (LPC_GPIO_TypeDef *) (LPC_GPIO_BASE + (uiportnum << 5));

	return ((GPIO_FIO_GET->FIOPIN >> uipinnum)&0x01);	
}

void GPIO_SetPinFunc( uint8_t uipinnum , uint8_t uipinfunc)
{
	uint8_t uiportnum;
	uint32_t *PINCON_PINSEL;
	
	uiportnum = uipinnum >> 5;
	uipinnum = uipinnum & 0x1F;
	
	uiportnum = uiportnum*2;
	
	if(uipinnum > 15)
	{
		uiportnum++;
		uipinnum = uipinnum%16;
	}
	
	PINCON_PINSEL = (uint32_t*)LPC_PINCON_BASE + uiportnum;
	
	*PINCON_PINSEL &= ~(0x3 << (uipinnum*2));			//Clear the function bits
	*PINCON_PINSEL |= (uipinfunc << (uipinnum*2)); //Enter the function bits
}

void GPIO_delay( uint16_t uidelay )
{
	uint16_t uiCount1=0, uiCount2=0;
	
	for( uiCount1 = 0; uiCount1 < 1024; uiCount1++)
		for( uiCount2 = 0; uiCount2 < uidelay; uiCount2++);
}
