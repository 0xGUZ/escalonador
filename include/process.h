#ifndef PROCESS_H
#define PROCESS_H

#include "io_type.h"

typedef enum
{
    NEW,
    READY,
    RUNNING,
    WAITING,
    TERMINATED
}
PROCESS_STATE;

typedef struct
{
    unsigned id;
    unsigned remaining_run_time;
    PROCESS_STATE state;
    unsigned priority;
    unsigned time_in_waiting;
    IO_TYPE io_type_waiting_for;
}
PROCESS_CONTROL_BLOCK;

typedef PROCESS_CONTROL_BLOCK PROCESS;

const char* process_state_name(PROCESS_STATE process_state);

PROCESS* new_process(unsigned id, unsigned remaining_run_time);

#endif
