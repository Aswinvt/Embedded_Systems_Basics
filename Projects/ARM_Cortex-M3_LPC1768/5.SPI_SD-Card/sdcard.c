#include "spi.h"
#include "sdcard.h"
#include "fat32.h"

uint8_t _SDCard_Int(uint8_t *cardtype);
uint8_t SDHighCapacityFlag = 0;

uint8_t SDCard_Int(uint8_t *cardtype)
{
    uint8_t response,retry=0;

    SPI_init();

    do
		{
			response = _SDCard_Int(cardtype);
			retry++;
    }while((response != SDCARD_INIT_SUCCESSFUL) && (retry!=10) );

    if(response == SDCARD_INIT_SUCCESSFUL)
    {
      response = getBootSectorData (); 																			//read boot sector and keep necessary data in global variables
    }
    return response;
}

uint8_t _SDCard_Int(uint8_t *cardtype)
{
	uint8_t  i, response, sd_version;
	uint16_t retry=0 ;
	
	for(i=0;i<10;i++)
		SPI_write(0xff);																												//Card enters native operating mode after 74 or more clock pulses
	
	GPIO_PinWrite(PIN0_16,LOW); 																							//Enabling CS
	
	do
	{
		response = SD_CMD(CMD0,0);
		retry++;
		if(retry>0x20){
			return SDCARD_NOT_DETECTED;}
	}while(response != 0x01);
	
	GPIO_PinWrite(PIN0_16,HIGH); 																							//Disabling CS
	
	SPI_write(0XFF);
  SPI_write(0XFF);
	
  retry = 0;

  sd_version = 2;
	
	do
  {
    response = SD_CMD(CMD8,0x000001AA);																			//Check power supply status, mendatory for SDHC card
    retry++;
    if(retry>0xfe)
    {
			sd_version = 1;
      *cardtype = SDCARD_TYPE_STANDARD;
      break;
    }																																				//time out
  }while(response != 0x01);

  retry = 0;

  do
	{
		response = SD_CMD(CMD55,0);																							//CMD55, must be sent before sending any ACMD command
    response = SD_CMD(ACMD41,0x40000000);																		//ACMD41

    retry++;
    if(retry>0xfe)
    {
			return SDCARD_INIT_FAILED;																						//time out, card initialization failed
    }

  }while(response != 0x00);

  retry = 0;
  SDHighCapacityFlag = 0;

  if (sd_version == 2)
  {
		do
    {
			response = SD_CMD(CMD58,0);
      retry++;
      if(retry>0xfe)
      {
				*cardtype = SDCARD_TYPE_UNKNOWN;
				break;
      }																																			//time out
    }while(response != 0x00);

    if(SDHighCapacityFlag == 1)
    {
			*cardtype = SDCARD_TYPE_HIGH_CAPACITY;
    }
    else
    {
			*cardtype = SDCARD_TYPE_STANDARD;
    }
  }
	return response;
}

unsigned char SD_CMD(unsigned char CMD, uint32_t arg)
{
	unsigned char response, retry=0, status;
	if(SDHighCapacityFlag == 0)
  {
		if(CMD == READ_SINGLE_BLOCK     ||
       CMD == READ_MULTIPLE_BLOCKS  ||
       CMD == WRITE_SINGLE_BLOCK    ||
       CMD == WRITE_MULTIPLE_BLOCKS ||
       CMD == ERASE_BLOCK_START_ADDR||
       CMD == ERASE_BLOCK_END_ADDR )
		{
			arg = arg << 9;
    }
  }


    GPIO_PinWrite(PIN0_16,LOW); 																						//Enabling CS


    SPI_write(CMD | 0x40);																									//send command, first two bits always '01'
    SPI_write(arg>>24);
    SPI_write(arg>>16);
    SPI_write(arg>>8);
    SPI_write(arg);


    if(CMD == CMD8)																													//it is compulsory to send correct CRC for CMD8 (CRC=0x87) & CMD0 (CRC=0x95)
        SPI_write(0x87);																										//for remaining commands, CRC is ignored in SPI mode
    else
        SPI_write(0x95);

    while((response = SPI_read()) == 0xFF)																	//wait response
        if(retry++ > 0xfe) break;																						//time out error

				if(response == 0x00 && CMD == 58)																		//checking response of CMD58
    {
        status = SPI_read() & 0x40;																					//first byte of the OCR register (bit 31:24)
        if(status == 0x40)
        {
            SDHighCapacityFlag = 1;																					//we need it to verify SDHC card
        }
        else
        {
            SDHighCapacityFlag = 0;
        }

        SPI_read();																													//remaining 3 bytes of the OCR register are ignored here
        SPI_read();																													//one can use these bytes to check power supply limits of SD
        SPI_read();
    }

    SPI_read();																															//extra 8 CLK
    GPIO_PinWrite(PIN0_16,HIGH); 																						//Disabling CS

    return response;																												//return state
}

unsigned char SD_erase (uint32_t startBlock, uint32_t totalBlocks)
{
    unsigned char response;

    response = SD_CMD(ERASE_BLOCK_START_ADDR, startBlock);									//send starting block address
    if(response != 0x00) 																										//check for SD status: 0x00 - OK (No flags set)
        return response;

    response = SD_CMD(ERASE_BLOCK_END_ADDR,(startBlock + totalBlocks - 1));	//send end block address
    if(response != 0x00)
        return response;

    response = SD_CMD(ERASE_SELECTED_BLOCKS, 0); 														//erase all selected blocks
    if(response != 0x00)
        return response;

    return 0;																																//normal return
}

unsigned char SD_readSingleBlock(char *inputbuffer,uint32_t startBlock)
{
	unsigned char response;
    uint16_t i, retry=0;

    response = SD_CMD(READ_SINGLE_BLOCK, startBlock); 											//read a Block command

    if(response != 0x00)
    {
        return response; 																										//check for SD status: 0x00 - OK (No flags set)
    }

    GPIO_PinWrite(PIN0_16,LOW); 																						//Enabling CS

    retry = 0;
    while(SPI_read() != 0xfe) 																							//wait for start block token 0xfe (0x11111110)
    {
        if(retry++ > 0xfffe)
        {
            GPIO_PinWrite(PIN0_16,HIGH); 																		//Disabling CS
            return 1; 																											//return if time-out
        }
    }

    for(i=0; i<512; i++) 																										//read 512 bytes
        inputbuffer[i] = SPI_read();

    SPI_read(); 																														//receive incoming CRC (16-bit), CRC is ignored here
    SPI_read();

    SPI_read(); 																														//extra 8 clock pulses
    GPIO_PinWrite(PIN0_16,HIGH); 																						//Disabling CS

    return 0;
}

unsigned char SD_writeSingleBlock(char *inputbuffer,uint32_t startBlock)
{
	    unsigned char response;
    uint16_t i, retry=0;

    response = SD_CMD(WRITE_SINGLE_BLOCK, startBlock); 											//write a Block command

    if(response != 0x00) return response; 																	//check for SD status: 0x00 - OK (No flags set)

    GPIO_PinWrite(PIN0_16,LOW); 																						//Enabling CS

    SPI_write(0xfe);     																										//Send start block token 0xfe (0x11111110)

    for(i=0; i<512; i++)    																								//send 512 bytes data
        SPI_write(inputbuffer[i]);

    SPI_write(0xff);     																										//transmit dummy CRC (16-bit), CRC is ignored here
    SPI_write(0xff);

    response = SPI_read();

    if( (response & 0x1f) != 0x05) 																					//response= 0xXXX0AAA1 ; AAA='010' - data accepted
    {                              																					//AAA='101'-data rejected due to CRC error
        GPIO_PinWrite(PIN0_16,HIGH);            														//AAA='110'-data rejected due to write error
        return response;
    }

    while(!SPI_read()) 																											//wait for SD card to complete writing and get idle
    {
        if(retry++ > 0xfffe)
        {
            GPIO_PinWrite(PIN0_16,HIGH); 																		//Disabling CS
            return 1;
        }
    }

    GPIO_PinWrite(PIN0_16,HIGH); 																						//Disabling CS
    SPI_write(0xff);   																											//just spend 8 clock cycle delay before reasserting the CS line
    GPIO_PinWrite(PIN0_16,LOW); 																	       	  //re-asserting the CS line to verify if card is still busy

    while(!SPI_read()) 																											//wait for SD card to complete writing and get idle
    {
        if(retry++ > 0xfffe)
        {
            GPIO_PinWrite(PIN0_16,HIGH); 																		//Disabling CS
            return 1;
        }
    }
    GPIO_PinWrite(PIN0_16,HIGH); 																						//Disabling CS

    return 0;
}
