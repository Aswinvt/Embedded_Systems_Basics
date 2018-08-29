#include "uart.h"
#include "gpio.h"
#include "delay.h"

void StartSignal(void);
void CheckResponse(void);
uint8_t ReadData(void);

uint8_t check;
char message1[] = "00.00 C";
char message2[] = "00.00 %";

int main(void)
{
	uint8_t Int_Byte_RH, Dec_Byte_RH , Int_Byte_Temp, Dec_Byte_Temp, Checksum;
	uart_int(9600);
	while(1)
	{
		GPIO_SetPinDir(PIN0_0,OUTPUT);		//For MCU signal, Pin is output
		StartSignal();
		GPIO_SetPinDir(PIN0_0,INPUT);			//After MCU signal, Pin is input
		CheckResponse();

		if(check == 1)
		{
			Int_Byte_RH = ReadData();
			Dec_Byte_RH = ReadData();
			Int_Byte_Temp = ReadData();
			Dec_Byte_Temp = ReadData();
			Checksum = ReadData();
			
			UART0_WriteString("\n\n\n\rData FROM DHT-11 SENSOR RECORDED!");
			
			if(Int_Byte_RH + Dec_Byte_RH + Int_Byte_Temp + Dec_Byte_Temp == Checksum)
			{
				UART0_WriteString("\n\n\rTemperature	:	");
				message1[0] = Int_Byte_Temp/10 + 48;
				message1[1] = Int_Byte_Temp%10 + 48;
				message1[3] = Dec_Byte_Temp/10 + 48;
				message1[4]	= Dec_Byte_Temp%10 + 48;
				message1[5] = 248;     											// Degree symbol
				UART0_WriteString(message1);
				
				UART0_WriteString("\n\rHumidity	:	");
				message2[0]  = Int_Byte_RH/10 + 48;
				message2[1]  = Int_Byte_RH%10 + 48;
				message2[3] = Dec_Byte_RH/10 + 48;
				message2[4]  = Dec_Byte_RH%10 + 48;
				UART0_WriteString(message2);
			}
			else
				UART0_WriteString("\n\rError in Data!");
		}
		else
			UART0_WriteString("\n\rNO RESPONSE FROM SENSOR!\n\r");
		DELAY_sec(5);
	}
}

void StartSignal(void)
{
	GPIO_PinWrite(PIN0_0,LOW);							//Pulling the PIN Low
  DELAY_ms(18);														//Low for atleast 18ms
	GPIO_PinWrite(PIN0_0,HIGH);							//Pulling the PIN High
}

void CheckResponse(void)
{
	check = 0;
	DELAY_us(40);
	if(GPIO_PinRead(PIN0_0) == 0)
	{
		DELAY_us(80);
		if(GPIO_PinRead(PIN0_0) == 1)
		{
			check = 1;
		}
		while(GPIO_PinRead(PIN0_0));					//Wait until Data goes LOW
	}
}

uint8_t ReadData(void)
{
	uint8_t i=0X00,j;
	for(j = 0; j < 8; j++)
	{
		while(!GPIO_PinRead(PIN0_0));					//Wait until Data goes HIGH
		DELAY_us(40);
		if(GPIO_PinRead(PIN0_0) == 0)
		{
			i&= ~(1<<(7 - j));  								//Clear bit (7-b)
		}
		else
		{
			i|= (1 << (7 - j));  								//Set bit (7-b)
			while(GPIO_PinRead(PIN0_0));   			//Wait until Data goes LOW
		}
	}
	return i;
}
