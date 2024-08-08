#include <stdbool.h>
#include "../headers/queue.h"   // Include for Queue related operations
#include "../headers/structs.h" // Include for PcbEntry
#include "../headers/operations.h"
#include "../headers/processController.h"

static int getHighestPriorityProcess()
{
}

static void executeCode()
{
    Instruction currentInstruction = cpu.program.instructions[cpu.programCounter];

    switch (currentInstruction.operation)
    {
    case 'S':
        S(currentInstruction.intArg);
        break;
    case 'A':
        A(currentInstruction.intArg);
        break;
    case 'D':
        D(currentInstruction.intArg);
        break;
    case 'B':
        B();
        break;
    case 'E':
        E();
        break;
    case 'F':
        F();
        break;
    case 'R':
        R(currentInstruction.stringArg);
        break;
    default:
        printf("Invalid operation on line %d. Please try again.\n", cpu.programCounter);
        break;
    }

    cpu.programCounter++;
    cpu.timeSliceUsed++;
    // need to act on when a process is complete --> remove from pcbTable, set runningState to -1, increment completeProcesses, calculate & increment turnaround time
}

static bool processIsComplete() { // unused so far
    return (cpu.programCounter == cpu.program.programSize);
}

void incrementTime()
{
    time++;

    int priorityProcessPid = getHighestPriorityProcess(); // ensure that running process is the highest priority; replace it if it isn't
    if (priorityProcessPid != runningState)
    {
        saveContext();
        loadContext(priorityProcessPid);
    }

    executeCode();
}