#include <lpc17xx.h>

#define TRUE 1
#define FALSE 0

#define BUFSIZE             	64
#define MAX_TIMEOUT         	0x00FFFFFF

#define AT24C16			        	0xA0

#define RD_BIT             	 	0x01

#define I2C_IDLE              0
#define I2C_STARTED           1
#define I2C_RESTARTED         2
#define I2C_REPEATED_START    3
#define DATA_ACK              4
#define DATA_NACK             5
#define I2C_BUSY              6
#define I2C_NO_DATA           7
#define I2C_NACK_ON_ADDRESS   8
#define I2C_NACK_ON_DATA      9
#define I2C_ARBITRATION_LOST  10
#define I2C_TIME_OUT          11
#define I2C_OK                12

#define I2EN       						(0x1<<6)  /* I2C Control Set Register */
#define AA         						(0x1<<2)
#define SI         						(0x1<<3)
#define STO        						(0x1<<4)
#define STA        						(0x1<<5)

#define I2SCLH_SCLH						0x00000080  /* I2C SCL Duty Cycle High Reg */
#define I2SCLL_SCLL						0x00000080  /* I2C SCL Duty Cycle Low Reg */

extern void I2C0_IRQHandler( void );
extern void I2C0_Init( void );
extern uint32_t I2C_Start( void );
extern uint32_t I2C_Stop( void );
extern uint32_t I2C_Engine( void );
