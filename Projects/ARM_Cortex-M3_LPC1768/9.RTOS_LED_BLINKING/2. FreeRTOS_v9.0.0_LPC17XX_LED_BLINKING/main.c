/*
 * File name            : main.c
 * Compiler             : MDK-Lite
 * IDE                  : Keil uVision V5
 * Author               : Etiq Technologies
 * Processor            : LPC1768
 * Created on           : November 29, 2017, 11:55 AM
 * Description          : LED Blinking Program Using FreeRTOS
 */
 
#include <lpc17xx.h>
#include "FreeRTOS.h"
#include "task.h"

#define LED1				16
#define LED2				17
#define LED3				18
#define IDEAL_LED		19

#define GPIO_PIN_DIR	LPC_GPIO0->FIODIR
#define GPIO_PIN_SET	LPC_GPIO0->FIOSET
#define GPIO_PIN_CLR	LPC_GPIO0->FIOSET

/* Local Functions for Tasks declaration */
void vTask1( void *pvParameters );
void vTask2( void *pvParameters );
void vTask3( void *pvParameters );
void vIdealTask( void *pvParameters );

int main(void)
{
	SystemInit();
	
	/*Setting Port0 Pins 16, 17, 18 & 19 as output for Task-1, Task-2, Task-3 & Ideal-Task*/
	GPIO_PIN_DIR |= (1<<LED1)|(1<<LED2)|(1<<LED3)|(1<<IDEAL_LED);
	
	/* Creating four tasks with priorities 1, 2, 3 and Ideal priority.*/
	xTaskCreate( vIdealTask,								/* Pointer to the function that implements the task. */
							 "IdealTask",								/* Text name for the task. This is to facilitate debugging only. */
							 configMINIMAL_STACK_SIZE,	/* The size of the stack that should be created for the task. 
																					 * This is defined in words, not bytes. */
							 NULL,											/* A reference to xParameters is used as the task parameter. 
																					 * This is cast to a void * to prevent compiler warnings.
																					 * This example does not use the task parameter. */
							 tskIDLE_PRIORITY,					/* The priority to assign to the newly created task. 
																					 * This task has Ideal Priority. */
							 NULL);											/* The handle to the task being created will be placed in xHandle. 
																					 * This example does not use the task handle. */
	xTaskCreate( vTask1, "Task1", configMINIMAL_STACK_SIZE, NULL, 1, NULL );
	xTaskCreate( vTask2, "Task2", configMINIMAL_STACK_SIZE, NULL, 2, NULL );
	xTaskCreate( vTask3, "Task3", configMINIMAL_STACK_SIZE, NULL, 3, NULL );
	
	/* Start the scheduler so the tasks start executing. */
	vTaskStartScheduler();	
	
	/* If all is well then main() will never reach here as the scheduler will 
	now be running the tasks. If main() does reach here then it is likely that 
	the idle task could not be created inside vTaskStartScheduler() or there was 
	insufficient heap memory available for the idle task to be created.*/
	while(1);
}

void vTask1(void *pvParameters)
{
	while(1)
	{
		GPIO_PIN_SET |= (1<LED1);					/*LED for Task-1 with priority 1*/
		vTaskDelay(500);
		GPIO_PIN_CLR |= (1<LED1);
		vTaskDelay(500);
	}
}

void vTask2(void *pvParameters)
{
	while(1)
	{
		GPIO_PIN_SET |= (1<LED2);					/*LED for Task-2 with priority 2*/
		vTaskDelay(1000);
		GPIO_PIN_SET |= (1<LED2);
		vTaskDelay(1000);
	}
}

void vTask3(void *pvParameters)
{
	while(1)
	{
		GPIO_PIN_SET |= (1<LED3);					/*LED for Task-3 with priority 3*/
		vTaskDelay(1500);
		GPIO_PIN_SET |= (1<LED3);
		vTaskDelay(1500);
	}
}

void vIdealTask(void *pvParameters)
{
	while(1)
	{
		GPIO_PIN_SET |= (1<IDEAL_LED);		/*LED for Ideal-Task*/
		vTaskDelay(1000);
		GPIO_PIN_SET |= (1<IDEAL_LED);
		vTaskDelay(1000);
	}
}
