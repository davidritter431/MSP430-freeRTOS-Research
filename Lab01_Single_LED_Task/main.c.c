// David Ritter 9/3/2026
// This code will create a task to toggle an LED and schedule it in the main function

// Including the MSP430 device definitions
#include <msp430.h> 
#include "FreeRTOS.h"
#include "task.h"

// Here are the dimensions of the buffer that the task being created will use as its stack.  
#define STACK_SIZE 200

// This provides the memory for the Task Control Block
StaticTask_t xTaskBuffer;

// Declaring xStack
StackType_t xStack[ STACK_SIZE ];

/* Creating a Task */
// void * pvParameters points at something
void vATaskFunction( void * pvParameters )
{
	// Infinite Loop
	for ( ;; )
	{
		// Task here
		P1OUT ^= BIT0;
		// This will wait 10 ticks
		vTaskDelay(10);
	}
}

// Creating the task
void vOtherFunction( void )
{
	TaskHandle_t xHandle = NULL;
	
	// Creating the task without dynamic memory allocation
	xHandle = xTaskCreateStatic(
					vATaskFunction,
					"Task_1",
					STACK_SIZE,
					(void *)1,
					tskIDLE_PRIORITY,
					xStack,
					&xTaskBuffer );

}

int main( void )
{
	// Hardware Initialization
	// = means assignment
	// == means comparison
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	// Bit manipulation
	P1OUT &= ~BIT0; // Clear the P1.0 output
	P1DIR |= BIT0;  // This sets the LED P1.0 as an output

	// Acts as a GPIO initialization
	PM5CTL0 &= ~LOCKLPM5; // Disable the GPIO power-on default high impedance mode
	
	// Create Task
	vOtherFunction();

	// Start scheduling the task
	vTaskStartScheduler();

	for(;;)
	{
	}
}
