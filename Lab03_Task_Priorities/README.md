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
- Experiment 3: Observing Task States During Runtime

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

vTaskDelay(10);

Observation:
When removing vTaskDelay(10); from task1, the LED from task1 was the only one on.  
The higher-priority task never entered the blocked state and continuously consumed the CPU time. 

### Experiment 3 

Observing task status during runtime

Task1 and Task2 use:

tskIDLE_PRIORITY

Task 1 observes Task2 using:

xTask2State = eTaskGetState(xHandle2);

Task 2 observes Task1 using:

xTask1State = eTaskGetState(xHandle1);

The task states are displayed in the CCS Watch window.

Observation:
Task1 and Task2 were able to observe the state of the other task during runtime. 
The CCS Watch window was used to view the values of xTask1State and xTask2State.

The possible task states observed are:

eRunning - The task is currently running
eReady - The task is ready to run
eBlocked - The task is waiting for an event or delay
eSuspended - The task has been suspended
eDeleted - The task has been deleted
