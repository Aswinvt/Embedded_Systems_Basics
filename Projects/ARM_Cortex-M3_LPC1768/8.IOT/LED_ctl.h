#define PORT0DIR LPC_GPIO0->FIODIR
#define PORT0SET LPC_GPIO0->FIOSET
#define PORT0CLR LPC_GPIO0->FIOCLR

#define LED1 16
#define LED2 17
#define LED3 18
#define LED4 19
#define LED5 20
#define LED6 21
#define LED7 22
#define LED8 23

void LED_ctrl(char c);
