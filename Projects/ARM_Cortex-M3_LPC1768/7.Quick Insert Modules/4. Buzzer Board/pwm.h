#include "gpio.h"

void PWM_Init( uint8_t uiPWMpin, uint16_t uiPWMperiod );		// Period in milliseconds
void PWM_UpdatePulseWidth( uint16_t uipulsewidth );
void TIMER_Init( void );
void Delay_ms( uint32_t uimillisec );
