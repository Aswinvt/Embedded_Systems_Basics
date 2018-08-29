#include <lpc17xx.h>
#include "gpio.h"
#include "delay_ms.h"

#define 	EINT_FUNC				 0x01
#define		EINT_CLR				 0x11
#define		EINT_0					 20
#define		EINT_1					 22
#define		EINT_2					 24
#define		EINT_3					 26

#define		LEVEL_SENSE		 	 0
#define		EDGE_SENSE		 	 1

#define		POL_LOWFALL 		 0
#define		POL_HIGHRISE 		 1

#define		EXTINT0					 0
#define		EXTINT1					 1
#define		EXTINT2					 2
#define		EXTINT3					 3
