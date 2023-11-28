#include "view.h"

#include "scheduler.h"
#include <stdio.h>

void view_show(void);
void view_await_input(void);

void view_print_process_queue(PROCESS_QUEUE* queue);
void view_print_process(PROCESS* process);

void view_show_until_input(void)
{
    view_show();
    view_await_input();
    view_put_separator();
}

void view_put_separator(void)
{
    printf("\n\n\n");
}

void view_show(void)
{
    unsigned priority, i;
    PROCESS_QUEUE_NODE* process_node;
    printf("Time: %u. Time in current quantum: %u.\n", scheduler_time, scheduler_time_in_quantum);
    printf("\n");
    if(scheduler_occurred_io_in_last_iteration())
    {
        printf("Process %u caused IO operation of type %s.\n", scheduler_process_that_caused_io_in_last_iteration->id,
                io_type_name(scheduler_process_that_caused_io_in_last_iteration->io_type_waiting_for));
        printf("\n");
    }
    printf("New queue: "); view_print_process_queue(scheduler_new_queue); printf("\n");
    printf("\n");
    printf("Ready queues:\n");
    for(priority = 0; priority < SCHEDULER_NUMBER_OF_READY_QUEUES; priority++)
    {
        printf("Priority %u: ", priority); view_print_process_queue(scheduler_ready_queues[priority]); printf("\n");
    }
    printf("\n");
    printf("Running process: ");
    if(scheduler_is_running_process())
    {
        printf("%u", scheduler_running_process->id);
    }
    else
    {
        printf("[None]");
    }
    printf(".\n");
    printf("\n");
    printf("Waiting queues:\n");
    for(i = 0; i < IO_TYPE_NUMBER_OF_TYPES; i++)
    {
        PROCESS_QUEUE* queue = scheduler_waiting_queue_for_io_type(IO_TYPE_TYPES[i]);
        printf("IO type %s: ", io_type_name(IO_TYPE_TYPES[i])); view_print_process_queue(queue); printf("\n");
    }
    printf("\n");
    printf("Terminated queue: "); view_print_process_queue(scheduler_terminated_queue); printf("\n");
    printf("\n");
    printf("All processes:\n");
    for(process_node = scheduler_all_processes->front; process_node != NULL; process_node = process_node->next)
    {
        view_print_process(process_node->process); printf("\n");
    }
    printf("\n");
    printf("Press [Enter] to iterate. ");
}

void view_await_input(void)
{
    while(getchar() != '\n');
}

void view_print_process_queue(PROCESS_QUEUE* queue)
{
    PROCESS_QUEUE_NODE* i;
    if(process_queue_is_empty(queue))
    {
        printf("[Empty]");
        return;
    }
    printf("[Front]");
    for(i = queue->front; i != NULL; i = i->next)
    {
        printf(" %d", i->process->id);
    }
    printf(" [Rear]");
}

void view_print_process(PROCESS* process)
{
    printf("[PID: %u] [State: %s]", process->id, process_state_name(process->state));
    switch(process->state)
    {
        case NEW:

            printf(" [Remaining run time: %u]", process->remaining_run_time);
            break;
        
        case READY:
        case RUNNING:

            printf(" [Remaining run time: %u]", process->remaining_run_time);
            printf(" [Priority: %u]", process->priority);
            break;
        
        case WAITING:

            printf(" [Remaining run time: %u]", process->remaining_run_time);
            printf(" [Priority: %u]", process->priority);
            printf(" [Time in waiting: %u]", process->time_in_waiting);
            printf(" [IO type waiting for: %s]", io_type_name(process->io_type_waiting_for));
        
        default: ;
    }
}
