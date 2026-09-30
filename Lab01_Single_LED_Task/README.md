# Lab 01 - Single LED Task

## Objective
Create a single freeRTOS task on the MSP430FR5994 that toggles an LED.  

## Hardware
- MSP430FR5994 LaunchPad
- MSP-EXP430FR5994 Development Board

## Software
- Code Composer Studio (CCS)
- freeRTOS v10.1.1
- MSP430Ware

## Concepts Demonstrated

- Static task allocation
- Task Control Blocks
- Task stacks
- freeRTOS schedule startup
- GPIO configuration
- Task delays using 'vTaskDelay()'

## Task Implementation

The task continuously toggles LED P1.0 and sleeps for a fixed numbe of scheduled ticks.  

for(;;)
{
  P1OUT ^= BIT0;
  vTaskDelay(10); 
}


