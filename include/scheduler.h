#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process_queue.h"

#define SCHEDULER_MAXIMUM_NUMBER_OF_ACTIVE_PROCESSES 30
#define SCHEDULER_NUMBER_OF_READY_QUEUES 2
#define SCHEDULER_QUANTUM 2

extern unsigned scheduler_number_of_active_processes;

extern unsigned scheduler_time;
extern unsigned scheduler_time_in_quantum;

extern PROCESS_QUEUE* scheduler_all_processes;

extern PROCESS_QUEUE* scheduler_new_queue;
extern PROCESS_QUEUE* scheduler_ready_queues[SCHEDULER_NUMBER_OF_READY_QUEUES];
extern PROCESS* scheduler_running_process;
extern PROCESS_QUEUE* scheduler_waiting_queues[IO_TYPE_NUMBER_OF_TYPES];
extern PROCESS_QUEUE* scheduler_terminated_queue;

extern PROCESS* scheduler_process_that_caused_io_in_last_iteration;

void scheduler_initialize(void);

int scheduler_is_running_process(void);

PROCESS_QUEUE* scheduler_waiting_queue_for_io_type(IO_TYPE io_type);

int scheduler_has_active_processes(void);

int scheduler_occurred_io_in_last_iteration(void);

void scheduler_iterate(void);

void scheduler_finish(void);

#endif
