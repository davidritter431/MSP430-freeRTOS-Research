# Lab 03 - Task Priorities

## Objective
Investigate how FreeRTOS task priorities affect execution.

## Hardware 
- MSP430FR5994 LaunchPad
- MSP-EXP430FR5994 Development Board

## Software 
- Code Composer Studio (CCS)
- freeRTOS v10.1.1
- MSP430Ware

## Concepts 
- Ready State
- Running State
- Blocked State
- Priority Scheduling
- Context Switching

## Experiments
- Experiment 1: Task1 priority
- Experiment 2: Task1 runs continously
- Experiment 3: Task1 Priority change during runtime

### Experiment 1
Changing the priority of one task over the other.  

Task1 Priority:

tskIDLE_PRIORITY + 1 // Adding priority to task 1 over task 2

Task2 Priority:

tskIDLE_PRIORITY // Leaving task 2 the same

Observation:  
When adding the + 1 to task 1, there was no visible difference.
The next step then was to remove the delay from task 1.

### Experiment 2

Removing the delay from a task

Task1 runs contimously.

Task2 uses:

vTaskDelay(25);

Observation:

### Experiment 3 

Changing the priority during runtime

Task1 and Task2 use:

tskIDLE_PRIORITY

Task1 adds: 
vTaskPrioritySet(NULL, tskIDLE_PRIORITY + 1);
