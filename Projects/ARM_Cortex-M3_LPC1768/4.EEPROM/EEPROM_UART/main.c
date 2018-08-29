#include "i2c.h"
#include "uart.h"

extern volatile uint8_t I2C_MasterBuffer[BUFSIZE];
extern volatile uint8_t I2C_SlaveBuffer[BUFSIZE];
extern volatile uint32_t I2C_ReadLength;
extern volatile uint32_t I2C_WriteLength;

int main (void)
{
  uint32_t i;
	
  SystemInit();
	
	uart_int(9600);											/* initialize UART */
	
  I2C0_Init();												/* initialize I2C0 */
	
  I2C_WriteLength = 13;
  I2C_ReadLength = 0;
  I2C_MasterBuffer[0] = AT24C16;			/*Address of EEPROM (A2=0,A1=0,A0=0 gives 0xA0)*/
  I2C_MasterBuffer[1] = 0x00;					/* address */
  I2C_MasterBuffer[2] = 'O';					/* Data0 */
  I2C_MasterBuffer[3] = 'p';					/* Data1 */
  I2C_MasterBuffer[4] = 'e';					/* Data2 */
  I2C_MasterBuffer[5] = 'n';					/* Data3 */
	I2C_MasterBuffer[6] = 'L';					/* Data4 */
	I2C_MasterBuffer[7] = 'a';					/* Data5 */
	I2C_MasterBuffer[8] = 'b';					/* Data6 */
	I2C_MasterBuffer[9] = ' ';					/* Data7 */
	I2C_MasterBuffer[10] = 'A';					/* Data8 */
	I2C_MasterBuffer[11] = 'R';					/* Data9 */
	I2C_MasterBuffer[12] = 'M';					/* Data10 */
  I2C_Engine();
	
  for ( i = 0; i < 0x200000; i++ );		/* Delay after write */
	
  for ( i = 0; i < BUFSIZE; i++ )
  {
		I2C_SlaveBuffer[i] = 0x00;
  }
	
  I2C_WriteLength = 2;
  I2C_ReadLength = 11;
  I2C_MasterBuffer[0] = AT24C16;
  I2C_MasterBuffer[1] = 0x00;
  I2C_MasterBuffer[2] = AT24C16 | RD_BIT;
  I2C_Engine();
	
	UART0_WriteString("\n\rDATA READ FROM EEPROM : ");
	for(i=0;i<11;i++)
	{
		UART0_WriteChar(I2C_SlaveBuffer[i]);
	}
  while (1);
}
