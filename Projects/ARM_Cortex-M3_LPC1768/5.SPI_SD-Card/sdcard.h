#include <stdint.h>

uint8_t SDCard_Int(uint8_t *cardtype);
unsigned char SD_CMD(unsigned char CMD, uint32_t arg);
unsigned char SD_readSingleBlock(char *inputbuffer,uint32_t startBlock);
unsigned char SD_writeSingleBlock(char *inputbuffer,uint32_t startBlock);

/***************************************************_SPI COMMAND SET_***********************************************************/

#define CMD0 												0					//Software reset.
#define CMD1 												1					//Initiate initialization process.
#define CMD8 												8					//For only SDC V2. Check voltage range.
#define CMD9 												9					//Read CSD register.
#define CMD10												10				//Read CID register.
#define CMD12												12				//Stop to read data.
#define CMD16												16				//Change R/W block size.
#define CMD17												17				//Read a block.
#define CMD18												18				//Read multiple blocks.
#define CMD23												23				//For only MMC. Define number of blocks to transfer with next multi-block read/write command.
#define CMD24												24				//Write a block.
#define CMD25												25				//Write multiple blocks.
#define CMD55												55				//Leading command of ACMD<n> command.
#define CMD58												58				//Read OCR.
#define ACMD41											41				//For only SDC. Initiate initialization process.
#define ACMD23											23				//For only SDC. Define number of blocks to pre-erase with next multi-block write command.
#define READ_SINGLE_BLOCK						17
#define READ_MULTIPLE_BLOCKS				18
#define WRITE_SINGLE_BLOCK					24
#define WRITE_MULTIPLE_BLOCKS				25
#define ERASE_BLOCK_START_ADDR			32
#define ERASE_BLOCK_END_ADDR				33
#define ERASE_SELECTED_BLOCKS				38

/********************************************************************************************************************************
*->1:ACMD<n> means a command sequense of CMD55-CMD<n>.
*********************************************************************************************************************************/

/***************************************************_SD CARD INIT STATUS_********************************************************/

#define SDCARD_INIT_SUCCESSFUL 			0
#define SDCARD_NOT_DETECTED    			1
#define SDCARD_INIT_FAILED     			2
#define SDCARD_FAT_INVALID     			3

#define SDCARD_TYPE_UNKNOWN        	0
#define SDCARD_TYPE_STANDARD       	1
#define SDCARD_TYPE_HIGH_CAPACITY  	2

/********************************************************************************************************************************/
