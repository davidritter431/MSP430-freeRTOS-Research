// David Ritter 10/8/2026
// Observing task states
// In this experiment, task 1 will observe what task 2 is doing and task 2 will observe what task 1 is doing

// To implement this experiment, I had to make sure that #define INCLUDE_eTaskGetState was set to 1 instead of 0 inside of FreeRTOSConfig.h

// Including the MSP430 device definitions
#include <msp430.h>
#include "FreeRTOS.h"
#include "task.h"

// Here are the dimensions of the buffer that the task being created will use as its stack.  
#define STACK_SIZE 200

// This provides the memory Control Block for Task 1 and Task 2 seperately
StaticTask_t xTaskBuffer1;
StaticTask_t xTaskBuffer2;

TaskHandle_t xHandle1 = NULL;
TaskHandle_t xHandle2 = NULL;

// Declaring xStack for task 1
StackType_t xStack1[ STACK_SIZE ];
// Declaring xStack for task 2
StackType_t xStack2[ STACK_SIZE ];

volatile eTaskState xTask1State;
volatile eTaskState xTask2State;

/* Creating a Task */
// void * pvParameters points at something
void Task1( void * pvParameters )
{
	// Infinite Loop
	for ( ;; )
	{
		// Task 1 here
		P1OUT ^= BIT0;
		
		// Investigating task 2
		// Asking what task 2 is doing and storing the answer in xTask1State
		xTask2State = eTaskGetState(xHandle2);

		// This will wait 10 ticks
		vTaskDelay(10);
	}
}

void Task2( void * pvParameters )
{
	// Infinite Loop
	for ( ;; )
	{
		// Task 2 here
		P1OUT ^= BIT1;
		
		// Investigate task 1
		// Asking what task 1 is doing and storing the answer in xTask2State
		xTask1State = eTaskGetState(xHandle1);

		// This will wait 10 ticks
		vTaskDelay(25);
	}
}

// Creating the task
void create_task1( void )
{

	// Creating the task without dynamic memory allocation
	xHandle1 = xTaskCreateStatic(
					Task1,
					"Task_1",
					STACK_SIZE,
					(void *)1,
					tskIDLE_PRIORITY,
					xStack1,
					&xTaskBuffer1);

}

// Creating the task
void create_task2( void )
{

	// Creating the task without dynamic memory allocation
	xHandle2 = xTaskCreateStatic(
					Task2,
					"Task_2",
					STACK_SIZE,
					(void *)1,
					tskIDLE_PRIORITY,
					xStack2,
					&xTaskBuffer2 );

}

int main( void )
{
	// Hardware Initialization
	// = means assignment
	// == means comparison
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	// Initialization of the GPIO
	
	// This is for the LED that is attached to Task 1
	// Bit manipulation
	P1OUT &= ~BIT0; // Clear the P1.0 output
	P1DIR |= BIT0;  // This sets the LED P1.0 as an output
	
	// The bit manipulation for Task 2 
	P1OUT &= ~BIT1; // Clear the P1.0 output
	P1DIR |= BIT1;  // This sets the LED P1.0 as an output

	// Acts as a GPIO initialization
	PM5CTL0 &= ~LOCKLPM5; // Disable the GPIO power-on default high impedance mode

	// Create Task
	create_task1();

	create_task2();

	// Start scheduling the task
	vTaskStartScheduler();

	for(;;)
	{
	}
}

