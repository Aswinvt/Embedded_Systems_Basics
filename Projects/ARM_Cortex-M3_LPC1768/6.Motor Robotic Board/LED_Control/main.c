#include <lpc17xx.h>
#include "softi2c.h"
#include "gpio.h"
#include "delay.h"

#define ADDR 0x80								// PCA9685 I2C address 0x80

int mode = 0;

int main()
{
	int i;
	SoftI2C_Init(P1_24,P1_25);		// Initialise I2C pins
	SoftI2C_Start();							// Initialise I2C communication
	SoftI2C_Write(ADDR);
	SoftI2C_Write(0x01);					// Select MODE2 register
	SoftI2C_Write(0x04);					// All pin's outputs are configured with a totem pole structure.
	SoftI2C_Stop();								// Stop I2C Transmission
	
	SoftI2C_Start();
	SoftI2C_Write(ADDR);
	SoftI2C_Write(0x00);					// Select MODE1 register
	SoftI2C_Write(0x01);					// Response to LED all-call I2C address
	SoftI2C_Stop();
	DELAY_ms(5);
	
	SoftI2C_Start();
	SoftI2C_Write(ADDR);
	SoftI2C_Write(0x00);
	SoftI2C_Stop();
	
	SoftI2C_Start();
	SoftI2C_Write(ADDR);
	mode = SoftI2C_Read(0x00);		// Read 1 byte of data
	SoftI2C_Stop();
	
	SoftI2C_Start();
	SoftI2C_Write(ADDR);
	SoftI2C_Write(0x00);					// Select MODE1 register
	SoftI2C_Write(0x10);					// Response to LED all-call I2C address
	SoftI2C_Stop();
	
	SoftI2C_Start();
	SoftI2C_Write(ADDR);
	SoftI2C_Write(0xFE);					// Select PRE_SCALE register
	SoftI2C_Write(0x65);					// Set prescale frequency to 60 Hz
	SoftI2C_Stop();
	
	SoftI2C_Start();
	SoftI2C_Write(ADDR);
	SoftI2C_Write(0x00);					// Select MODE1 register
	SoftI2C_Write(mode);
	SoftI2C_Stop();
	DELAY_ms(5);
	
	SoftI2C_Start();
	SoftI2C_Write(ADDR);
	SoftI2C_Write(0x00);					// Select MODE1 register
	SoftI2C_Write((mode|0x80));
	SoftI2C_Stop();
	
	while(1)
	{
		for (i = 0; i < 4096; i += 3)
		{
			SoftI2C_Start();
			SoftI2C_Write(ADDR);
			SoftI2C_Write(0xFA);			// Select ALL_LED_ON_L register
			SoftI2C_Write(0x00);			// ALL_LED_ON lower byte
			SoftI2C_Stop();
			
			SoftI2C_Start();
			SoftI2C_Write(ADDR);
			SoftI2C_Write(0xFB);			// Select ALL_LED_ON_H register
			SoftI2C_Write(0x00);			// ALL_LED_ON higher byte
			SoftI2C_Stop();
			
			
			SoftI2C_Start();
			SoftI2C_Write(ADDR);
			SoftI2C_Write(0xFC);			// Select ALL_LED_OFF_L register
			SoftI2C_Write((i & 0xFF));// ALL_LED_OFF lower byte
			SoftI2C_Stop();
			
			SoftI2C_Start();
			SoftI2C_Write(ADDR);
			SoftI2C_Write(0xFD);			// Select ALL_LED_OFF_H register
			SoftI2C_Write((i >> 8));	// ALL_LED_OFF higher byte
			SoftI2C_Stop();
			DELAY_ms(1);
		}
		DELAY_ms(1000);
		
		for (i = 4095; i > 4096; i -= 3)
		{
			SoftI2C_Start();
			SoftI2C_Write(ADDR);
			SoftI2C_Write(0xFA);			// Select ALL_LED_ON_L register
			SoftI2C_Write(0x00);			// ALL_LED_ON lower byte
			SoftI2C_Stop();
			
			SoftI2C_Start();
			SoftI2C_Write(ADDR);
			SoftI2C_Write(0xFB);			// Select ALL_LED_ON_H register
			SoftI2C_Write(0x00);			// ALL_LED_ON higher byte
			SoftI2C_Stop();
			
			
			SoftI2C_Start();
			SoftI2C_Write(ADDR);
			SoftI2C_Write(0xFC);			// Select ALL_LED_OFF_L register
			SoftI2C_Write((i & 0xFF));// ALL_LED_OFF lower byte
			SoftI2C_Stop();
			
			SoftI2C_Start();
			SoftI2C_Write(ADDR);
			SoftI2C_Write(0xFD);		// Select ALL_LED_OFF_H register
			SoftI2C_Write((i >> 8));// ALL_LED_OFF higher byte
			SoftI2C_Stop();
			DELAY_ms(1);
		}
		DELAY_ms(1000);
	}
}
