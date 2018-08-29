#include "spi.h"
#include "uart_int.h"
#include "uart.h"
#include "sdcard.h"


int main()
{
	uint8_t returnStatus,sdcardtype;
	SystemInit();
	uart_int(9600);
  returnStatus = SDCard_Int(&sdcardtype);
	if(returnStatus)
    {
			if(returnStatus == SDCARD_NOT_DETECTED)
			{
				UART0_WriteString("\n\r SD card not detected..");
			}
			else if(returnStatus == SDCARD_INIT_FAILED)
			{
				UART0_WriteString("\n\r Card Initialization failed..");
			}
			else if(returnStatus == SDCARD_FAT_INVALID)
			{
				UART0_WriteString("\n\r Invalid Fat filesystem");
			}
			while(1);
	}
	else
  {
		UART0_WriteString("\n\rSD Card Detected!");
  }
}
