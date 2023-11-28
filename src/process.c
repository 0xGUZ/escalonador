#include "process.h"

#include <stdlib.h>
#include <stdio.h>

const char* process_state_name(PROCESS_STATE process_state)
{
    switch(process_state)
    {
        case NEW:           return "New";
        case READY:         return "Ready";
        case RUNNING:       return "Running";
        case WAITING:       return "Waiting";
        case TERMINATED:    return "Terminated";
    }
    return "Undefined";
}

PROCESS* new_process(unsigned id, unsigned remaining_run_time)
{
    PROCESS* process = (PROCESS*) malloc(sizeof(PROCESS));
    if(process == NULL)
    {
        fprintf(stderr, "Error: Could not allocate memory for process.");
        exit(7);
    }
    process->id = id;
    process->remaining_run_time = remaining_run_time;
    process->state = NEW;
    return process;
}
