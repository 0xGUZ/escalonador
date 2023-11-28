#include "scheduler.h"

#include <stdlib.h>
#include <stdio.h>
#include "input_records.h"

unsigned scheduler_number_of_active_processes;

unsigned scheduler_time;
unsigned scheduler_time_in_quantum;

PROCESS_QUEUE* scheduler_all_processes;

PROCESS_QUEUE* scheduler_new_queue;
PROCESS_QUEUE* scheduler_ready_queues[SCHEDULER_NUMBER_OF_READY_QUEUES];
PROCESS* scheduler_running_process;
PROCESS_QUEUE* scheduler_waiting_queues[IO_TYPE_NUMBER_OF_TYPES];
PROCESS_QUEUE* scheduler_terminated_queue;

PROCESS* scheduler_process_that_caused_io_in_last_iteration;

int scheduler_is_at_start_of_quantum(void);

void scheduler_iterate_before_time(void);
void scheduler_iterate_after_time(void);

void scheduler_iterate_running_process(void);
void scheduler_put_running_process_to_wait(void);
void scheduler_terminate_running_process(void);
void scheduler_iterate_time(void);
void scheduler_read_input_records(void);

void scheduler_admit_new_processes(void);
void scheduler_iterate_waiting_processes(void);
void scheduler_make_running_process_ready(void);

PROCESS_QUEUE* scheduler_waiting_queue_for_io_type(IO_TYPE io_type);

void scheduler_put_next_ready_process_to_run(void);
unsigned scheduler_best_priority_with_ready_processes(void);

void scheduler_initialize(void)
{
    unsigned i;
    scheduler_number_of_active_processes = 0;
    scheduler_time = 0;
    scheduler_time_in_quantum = 0;
    scheduler_all_processes = new_process_queue();
    scheduler_new_queue = new_process_queue();
    for(i = 0; i < SCHEDULER_NUMBER_OF_READY_QUEUES; i++)
    {
        scheduler_ready_queues[i] = new_process_queue();
    }
    scheduler_running_process = NULL;
    for(i = 0; i < IO_TYPE_NUMBER_OF_TYPES; i++)
    {
        scheduler_waiting_queues[i] = new_process_queue();
    }
    scheduler_terminated_queue = new_process_queue();
    scheduler_iterate_before_time();
}

int scheduler_is_running_process(void)
{
    return scheduler_running_process != NULL;
}

PROCESS_QUEUE* scheduler_waiting_queue_for_io_type(IO_TYPE io_type)
{
    switch(io_type)
    {
        case DISK:              return scheduler_waiting_queues[0];
        case MAGNETIC_TAPE:     return scheduler_waiting_queues[1];
        case PRINTER:           return scheduler_waiting_queues[2];
    }
    return NULL;
}

void scheduler_iterate(void)
{
    scheduler_iterate_after_time();
    scheduler_iterate_before_time();
}

void scheduler_finish(void)
{
    unsigned i;
    process_queue_free(scheduler_all_processes);
    process_queue_free(scheduler_new_queue);
    for(i = 0; i < SCHEDULER_NUMBER_OF_READY_QUEUES; i++)
    {
        process_queue_free(scheduler_ready_queues[i]);
    }
    for(i = 0; i < IO_TYPE_NUMBER_OF_TYPES; i++)
    {
        process_queue_free(scheduler_waiting_queues[i]);
    }
    process_queue_free(scheduler_terminated_queue);
}

int scheduler_has_active_processes(void)
{
    return scheduler_number_of_active_processes > 0;
}

int scheduler_occurred_io_in_last_iteration(void)
{
    return scheduler_process_that_caused_io_in_last_iteration != NULL;
}

int scheduler_is_at_start_of_quantum(void)
{
    return scheduler_time_in_quantum == 0;
}

void scheduler_iterate_before_time(void)
{
    scheduler_read_input_records();
    scheduler_admit_new_processes();
    scheduler_make_running_process_ready(); 
    scheduler_put_next_ready_process_to_run();
}

void scheduler_iterate_after_time(void)
{
    scheduler_iterate_waiting_processes();
    scheduler_iterate_running_process();
    scheduler_iterate_time();
}

void scheduler_iterate_running_process(void)
{
    unsigned random_number, i;
    scheduler_process_that_caused_io_in_last_iteration = NULL;
    if(!scheduler_is_running_process()) return;
    random_number = rand() % 100;
    for(i = 0; i < IO_TYPE_NUMBER_OF_TYPES; i++)
    {
        unsigned chance_to_occur = io_type_chance_to_occur(IO_TYPE_TYPES[i]);
        if(random_number < chance_to_occur)
        {
            scheduler_running_process->io_type_waiting_for = IO_TYPE_TYPES[i];
            scheduler_process_that_caused_io_in_last_iteration = scheduler_running_process;
            scheduler_put_running_process_to_wait();
            return;
        }
        random_number -= chance_to_occur;
    }
    scheduler_running_process->remaining_run_time--;
    if(scheduler_running_process->remaining_run_time == 0)
    {
        scheduler_terminate_running_process();
    }
}

void scheduler_put_running_process_to_wait(void)
{
    process_queue_enqueue(scheduler_waiting_queue_for_io_type(scheduler_running_process->io_type_waiting_for), scheduler_running_process);
    scheduler_running_process->state = WAITING;
    scheduler_running_process->time_in_waiting = 0;
    scheduler_running_process = NULL;
}

void scheduler_terminate_running_process(void)
{
    process_queue_enqueue(scheduler_terminated_queue, scheduler_running_process);
    scheduler_running_process->state = TERMINATED;
    scheduler_running_process = NULL;
    scheduler_number_of_active_processes--;
}

void scheduler_iterate_time(void)
{
    scheduler_time++;
    scheduler_time_in_quantum++;
    if(scheduler_time_in_quantum == SCHEDULER_QUANTUM)
    {
        scheduler_time_in_quantum = 0;
    }
}

void scheduler_read_input_records(void)
{
    PROCESS* process;
    INPUT_RECORD next_process_record;
    if(input_records_are_finished()) return;
    input_records_read_next(&next_process_record);
    while(!input_records_are_finished() && next_process_record.starting_time == scheduler_time)
    {
        process = new_process(next_process_record.pid, next_process_record.run_time);
        process_queue_enqueue(scheduler_all_processes, process);
        process_queue_enqueue(scheduler_new_queue, process);
        input_records_discard_next();
        input_records_read_next(&next_process_record);
    }
}

void scheduler_admit_new_processes(void)
{
    while(!process_queue_is_empty(scheduler_new_queue) && scheduler_number_of_active_processes < SCHEDULER_MAXIMUM_NUMBER_OF_ACTIVE_PROCESSES)
    {
        PROCESS* process = scheduler_new_queue->front->process;
        process_queue_enqueue(scheduler_ready_queues[0], process);
        process->state = READY;
        process->priority = 0;
        process_queue_dequeue(scheduler_new_queue);
        scheduler_number_of_active_processes++;
    }
}

void scheduler_iterate_waiting_processes(void)
{
    unsigned i;
    for(i = 0; i < IO_TYPE_NUMBER_OF_TYPES; i++)
    {
        PROCESS_QUEUE* waiting_queue = scheduler_waiting_queue_for_io_type(IO_TYPE_TYPES[i]);
        PROCESS* process;
        unsigned new_process_priority;
        if(process_queue_is_empty(waiting_queue)) continue;
        process = waiting_queue->front->process;
        process->time_in_waiting++;
        if(process->time_in_waiting == io_type_duration(process->io_type_waiting_for))
        {
            new_process_priority = io_type_priority_for_process_after_io_completion(process->io_type_waiting_for);
            process_queue_enqueue(scheduler_ready_queues[new_process_priority], process);
            process->state = READY;
            process->priority = new_process_priority;
            process_queue_dequeue(waiting_queue);
        }
    }
}

void scheduler_make_running_process_ready(void)
{
    unsigned new_priority;
    if(!scheduler_is_running_process()) return;
    if(!scheduler_is_at_start_of_quantum()) return;
    new_priority = scheduler_running_process->priority + 1;
    if(new_priority >= SCHEDULER_NUMBER_OF_READY_QUEUES)
    {
        new_priority = SCHEDULER_NUMBER_OF_READY_QUEUES - 1;
    }
    process_queue_enqueue(scheduler_ready_queues[new_priority], scheduler_running_process);
    scheduler_running_process->state = READY;
    scheduler_running_process->priority = new_priority;
    scheduler_running_process = NULL;
}

void scheduler_put_next_ready_process_to_run(void)
{
    unsigned priority_of_next_process_to_run;
    if(scheduler_is_running_process()) return;
    if(!scheduler_is_at_start_of_quantum()) return;
    priority_of_next_process_to_run = scheduler_best_priority_with_ready_processes();
    if(priority_of_next_process_to_run == SCHEDULER_NUMBER_OF_READY_QUEUES) return;
    scheduler_running_process = scheduler_ready_queues[priority_of_next_process_to_run]->front->process;
    scheduler_running_process->state = RUNNING;
    process_queue_dequeue(scheduler_ready_queues[priority_of_next_process_to_run]);
}

unsigned scheduler_best_priority_with_ready_processes(void)
{
    unsigned priority;
    for(priority = 0; priority < SCHEDULER_NUMBER_OF_READY_QUEUES; priority++)
    {
        if(!process_queue_is_empty(scheduler_ready_queues[priority]))
        {
            return priority;
        }
    }
    return SCHEDULER_NUMBER_OF_READY_QUEUES;
}
