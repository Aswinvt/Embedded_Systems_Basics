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

void GPIO_PinWrite(uint8_t uipinnum, uint8_t uidirection)
{
	uint8_t uiportnum;
	LPC_GPIO_TypeDef *GPIO_FIO_DIR;
	
	uiportnum = uipinnum >> 5;
	uipinnum = uipinnum & 0x1F;
	
	GPIO_FIO_DIR = (LPC_GPIO_TypeDef *) (LPC_GPIO_BASE + (uiportnum << 5));
	
	if(uidirection == HIGH)
		GPIO_FIO_DIR->FIOSET |= (1 << uipinnum);
	
	else if(uidirection == LOW)
		GPIO_FIO_DIR->FIOCLR |= (1 << uipinnum);
}

uint8_t GPIO_PinRead(uint8_t uipinnum)
{
	uint8_t uiportnum, Read_Pin;
	LPC_GPIO_TypeDef *GPIO_FIO_DIR;
	
	uiportnum = uipinnum >> 5;
	uipinnum = uipinnum & 0x1F;
	
	GPIO_FIO_DIR = (LPC_GPIO_TypeDef *) (LPC_GPIO_BASE + (uiportnum << 5));

	Read_Pin = (GPIO_FIO_DIR->FIOPIN & (1 << uipinnum))>>uipinnum;
	
	return Read_Pin;
}
