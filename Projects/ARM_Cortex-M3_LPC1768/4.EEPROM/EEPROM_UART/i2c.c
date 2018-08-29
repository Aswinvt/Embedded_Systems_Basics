#include "i2c.h"

volatile uint32_t I2C_MasterState = I2C_IDLE;
volatile uint32_t timeout = 0;

volatile uint8_t I2C_MasterBuffer[BUFSIZE];
volatile uint8_t I2C_SlaveBuffer[BUFSIZE];
volatile uint32_t I2C_Count = 0;
volatile uint32_t I2C_ReadLength;
volatile uint32_t I2C_WriteLength;

volatile uint32_t RdIndex0 = 0, RdIndex1 = 0, RdIndex2 = 0;
volatile uint32_t WrIndex0 = 0, WrIndex1 = 0, WrIndex2 = 0;

/*****************************************************************************
** Function name	:		I2C_IRQHandler
**
** Descriptions		:		I2C interrupt handler, deal with master mode only.
**
** parameters			:		None
** Returned value	:		None
** 
*****************************************************************************/
void I2C0_IRQHandler(void) 
{
	uint8_t StatValue;
	
  timeout = 0;
  /* this handler deals with master read and master write only */
  StatValue = LPC_I2C0->I2STAT;
  switch ( StatValue )
  {
		case 0x08:			/* A Start condition is issued. */
			WrIndex0 = 0;
			LPC_I2C0->I2DAT = I2C_MasterBuffer[WrIndex0++];
			LPC_I2C0->I2CONCLR = (SI | STA);
		break;
		
		case 0x10:			/* A repeated started is issued */
			RdIndex0 = 0;
			/* Send SLA with R bit set, */
			LPC_I2C0->I2DAT = I2C_MasterBuffer[WrIndex0++];
			LPC_I2C0->I2CONCLR = (SI | STA);
		break;
		
		case 0x18:			/* Regardless, it's a ACK */
			if ( I2C_WriteLength == 1 )
			{
				LPC_I2C0->I2CONSET = STO;      /* Set Stop flag */
				I2C_MasterState = I2C_NO_DATA;
			}
			else
			{
				LPC_I2C0->I2DAT = I2C_MasterBuffer[WrIndex0++];
			}
			LPC_I2C0->I2CONCLR = SI;
		break;
		
		case 0x28:	/* Data byte has been transmitted, regardless ACK or NACK */
			if ( WrIndex0 < I2C_WriteLength )
			{   
				LPC_I2C0->I2DAT = I2C_MasterBuffer[WrIndex0++]; /* this should be the last one */
			}
			else
			{
				if ( I2C_ReadLength != 0 )
				{
				LPC_I2C0->I2CONSET = STA;	/* Set Repeated-start flag */
				}
				else
				{
				LPC_I2C0->I2CONSET = STO;      /* Set Stop flag */
				I2C_MasterState = I2C_OK;
				}
			}
			LPC_I2C0->I2CONCLR = SI;
		break;
		
		case 0x30:
			LPC_I2C0->I2CONSET = STO;      /* Set Stop flag */
			I2C_MasterState = I2C_NACK_ON_DATA;
			LPC_I2C0->I2CONCLR = SI;
		break;
		
		case 0x40:	/* Master Receive, SLA_R has been sent */
			if ( (RdIndex0 + 1) < I2C_ReadLength )
			{
				/* Will go to State 0x50 */
				LPC_I2C0->I2CONSET = AA;	/* assert ACK after data is received */
			}
			else
			{
				/* Will go to State 0x58 */
				LPC_I2C0->I2CONCLR = AA;	/* assert NACK after data is received */
			}
			LPC_I2C0->I2CONCLR = SI;
		break;
		
		case 0x50:	/* Data byte has been received, regardless following ACK or NACK */
			I2C_SlaveBuffer[RdIndex0++] = LPC_I2C0->I2DAT;
			if ( (RdIndex0 + 1) < I2C_ReadLength )
			{   
				LPC_I2C0->I2CONSET = AA;	/* assert ACK after data is received */
			}
			else
			{
				LPC_I2C0->I2CONCLR = AA;	/* assert NACK on last byte */
			}
			LPC_I2C0->I2CONCLR = SI;
		break;
		
		case 0x58:
			I2C_SlaveBuffer[RdIndex0++] = LPC_I2C0->I2DAT;
			I2C_MasterState = I2C_OK;
			LPC_I2C0->I2CONSET = STO;	/* Set Stop flag */ 
			LPC_I2C0->I2CONCLR = SI;	/* Clear SI flag */
		break;
		
		case 0x20:		/* regardless, it's a NACK */
		case 0x48:
			LPC_I2C0->I2CONSET = STO;      /* Set Stop flag */
			I2C_MasterState = I2C_NACK_ON_ADDRESS;
			LPC_I2C0->I2CONCLR = SI;
		break;
		
		case 0x38:		/* Arbitration lost, in this example, we don't
						deal with multiple master situation */
		default:
			I2C_MasterState = I2C_ARBITRATION_LOST;
			LPC_I2C0->I2CONCLR = SI;	
		break;
  }
  return;
}

/*****************************************************************************
** Function name	:		I2CStart
**
** Descriptions		:		Create I2C start condition, a timeout
**										value is set if the I2C never gets started,
**										and timed out. It's a fatal error. 
**
** parameters			:		None
** Returned value	:		true or false, return false if timed out
** 
*****************************************************************************/
uint32_t I2C_Start()
{
  uint32_t retVal = FALSE;
	
  timeout = 0;
  /*--- Issue a start condition ---*/
  LPC_I2C0->I2CONSET = STA;	/* Set Start flag */
  
  /*--- Wait until START transmitted ---*/
  while(1)
  {
	if ( I2C_MasterState == I2C_STARTED )
	{
	  retVal = TRUE;
	  break;	
	}
	if ( timeout >= MAX_TIMEOUT )
	{
	  retVal = FALSE;
	  break;
	}
	timeout++;
  }
  return( retVal );
}

/*****************************************************************************
** Function name	:		I2CStop
**
** Descriptions		:		Set the I2C stop condition, if the routine
**										never exit, it's a fatal bus error.
**
** parameters			:		None
** Returned value	:		true or never return
** 
*****************************************************************************/
uint32_t I2C_Stop()
{
  LPC_I2C0->I2CONSET = STO;      /* Set Stop flag */ 
  LPC_I2C0->I2CONCLR = SI;  /* Clear SI flag */ 
         
  /*--- Wait for STOP detected ---*/
  while( LPC_I2C0->I2CONSET & STO );
  return TRUE;
}

/*****************************************************************************
** Function name	:		I2CInit
**
** Descriptions		:		Initialize I2C controller as a master
**
** parameters			:		None
** Returned value	:		None
** 
*****************************************************************************/
void I2C0_Init( void ) 
{
  LPC_SC->PCONP |= (1 << 7);
	
  /* set PIO0.27 and PIO0.28 to I2C0 SDA and SCL */
  /* function to 01 on both SDA and SCL. */
  LPC_PINCON->PINSEL1 &= ~((0x03<<22)|(0x03<<24));
  LPC_PINCON->PINSEL1 |= ((0x01<<22)|(0x01<<24));	
	
  /*--- Clear flags ---*/
  LPC_I2C0->I2CONCLR = AA | SI | STA | I2EN;    
	
  /*--- Reset registers ---*/
  LPC_PINCON->I2CPADCFG &= ~((0x1<<0)|(0x1<<2));
  LPC_I2C0->I2SCLL   = I2SCLL_SCLL;
  LPC_I2C0->I2SCLH   = I2SCLH_SCLH;
	
  /* Install interrupt handler */
  NVIC_EnableIRQ(I2C0_IRQn);
	
  LPC_I2C0->I2CONSET = I2EN;
  return;
}

/*****************************************************************************
** Function name	:		I2CEngine
**
** Descriptions		:		The routine to complete a I2C transaction
**										from start to stop. All the intermitten
**										steps are handled in the interrupt handler.
**										Before this routine is called, the read
**										length, write length, I2C master buffer,
**										and I2C command fields need to be filled.
**										see i2cmst.c for more details. 
**
** parameters			:		I2C port number
** Returned value	:		master state of current I2C port.
** 
*****************************************************************************/
uint32_t I2C_Engine() 
{
  /*--- Issue a start condition ---*/
  LPC_I2C0->I2CONSET = STA;	/* Set Start flag */
	
  I2C_MasterState = I2C_BUSY;	
	
  while ( I2C_MasterState == I2C_BUSY )
  {
		if ( timeout >= MAX_TIMEOUT )
		{
			I2C_MasterState = I2C_TIME_OUT;
			break;
		}
		timeout++;
  }
  LPC_I2C0->I2CONCLR = STA;
	
  return ( I2C_MasterState );
}
