#include "spi.h"

uint8_t dummy_u8;
uint32_t Freq;

void SPI_init( void )
{
	GPIO_SetPinFunc(PIN0_15,PINFUNC3);																				//SCK
	GPIO_SetPinFunc(PIN0_17,PINFUNC3);																				//MISO
	GPIO_SetPinFunc(PIN0_18,PINFUNC3);																				//MOSI
	
	GPIO_SetPinDir(PIN0_15,OUTPUT);																						//SCK
	GPIO_SetPinDir(PIN0_16,OUTPUT);																						//SSEL as GPIO
	GPIO_SetPinDir(PIN0_17,INPUT);																						//MISO
	GPIO_SetPinDir(PIN0_18,OUTPUT);																						//MOSI
	
	GPIO_PinWrite(PIN0_16,HIGH); 																							//Disabling CS
	
	LPC_SC->PCONP |= (1<<8);
	
	Freq = SystemCoreClock/4;
	LPC_SPI->SPCCR = Freq/4000000;
	
	LPC_SPI->SPCR = (0<<3)|(1<<4)|(1<<5);
	
	dummy_u8  = LPC_SPI->SPSR;
  dummy_u8  = LPC_SPI->SPDR;
}

uint8_t SPI_write( uint8_t _8bitData)
{
	LPC_SPI->SPDR = _8bitData;
	while(!((LPC_SPI->SPSR>>7)&0x01));
	dummy_u8 = LPC_SPI->SPSR;
  dummy_u8 = LPC_SPI->SPDR;
	dummy_u8 = 0;
	return _8bitData;
}

uint8_t SPI_read(void)
{
	uint8_t _8bitData;
	LPC_SPI->SPDR = 0xff;
	while(!((LPC_SPI->SPSR>>7)&0x01));
	dummy_u8 = LPC_SPI->SPSR;
	_8bitData = (uint8_t)LPC_SPI->SPDR; 
	dummy_u8 = 0;
	return _8bitData;
}
