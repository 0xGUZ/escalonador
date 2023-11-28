#ifndef PROCESS_QUEUE_H
#define PROCESS_QUEUE_H

#include "process.h"

typedef struct _PROCESS_QUEUE_NODE
{
    PROCESS* process;
    struct _PROCESS_QUEUE_NODE* next;
}
PROCESS_QUEUE_NODE;

typedef struct
{
    PROCESS_QUEUE_NODE* front;
    PROCESS_QUEUE_NODE* rear;
    unsigned size;
}
PROCESS_QUEUE;

PROCESS_QUEUE* new_process_queue(void);

void process_queue_enqueue(PROCESS_QUEUE* queue, PROCESS* process);
void process_queue_dequeue(PROCESS_QUEUE* queue);

int process_queue_is_empty(PROCESS_QUEUE* queue);

void process_queue_clear(PROCESS_QUEUE* queue);
void process_queue_free(PROCESS_QUEUE* queue);

#endif
