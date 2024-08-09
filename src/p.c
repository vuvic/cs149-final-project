#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../headers/structs.h"
#include "../headers/globals.h"

static void reporterProcess()
{ // to be completed
    printf("\n****************************************************************\n");
    printf("The current system state is as follows:\n");
    printf("****************************************************************\n\n");

    printf("CURRENT TIME: %d\n\n", time);

    if (runningState == -1)
    {
        printf("There is currently no process running.\n");
    }
    else
    {
        PcbEntry runningP = pcbTable[runningState];
        printf("RUNNING PROCESS: \n");
        printf("PID: %d, PPID: %d, Priority: %d, Value: %d, Start Time: %d, CPU Time Used: %d\n",
               runningP.processId, runningP.parentProcessId, runningP.priority, cpu.value, runningP.startTime, cpu.timeSliceUsed);
    }
    printQueue(&readyState[3]);
    printQueue(&readyState[2]);
    printQueue(&readyState[1]);
    printQueue(&readyState[0]);
    printQueue(&blockedState);
    return;
}

void printReport()
{
    // Spawn a reporter process
    if (fork() == 0)
    {
        reporterProcess();
        exit(0);
    }
    wait(NULL);
}