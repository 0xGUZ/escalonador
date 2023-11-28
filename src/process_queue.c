#include "process_queue.h"

#include <stdlib.h>
#include <stdio.h>

PROCESS_QUEUE* new_process_queue(void)
{
    PROCESS_QUEUE* queue = (PROCESS_QUEUE*) malloc(sizeof(PROCESS_QUEUE));
    if(queue == NULL)
    {
        fprintf(stderr, "Error: Could not allocate memory for process queue.");
        exit(5);
    }
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
    return queue;
}

void process_queue_enqueue(PROCESS_QUEUE* queue, PROCESS* process)
{
    PROCESS_QUEUE_NODE* new_node = (PROCESS_QUEUE_NODE*) malloc(sizeof(PROCESS_QUEUE_NODE));
    if(new_node == NULL)
    {
        fprintf(stderr, "Error: Could not allocate memory for process queue node.");
        exit(6);
    }
    new_node->process = process;
    new_node->next = NULL;
    if(process_queue_is_empty(queue))
    {
        queue->front = new_node;
        queue->rear = new_node;
    }
    else
    {
        queue->rear->next = new_node;
        queue->rear = new_node;
    }
    queue->size++;
}

void process_queue_dequeue(PROCESS_QUEUE* queue)
{
    PROCESS_QUEUE_NODE* old_node;
    if(process_queue_is_empty(queue)) return;
    old_node = queue->front;
    queue->front = old_node->next;
    if(queue->size == 1) queue->rear = NULL;
    queue->size--;
    free(old_node);
}

int process_queue_is_empty(PROCESS_QUEUE* queue)
{
    return queue->size == 0;
}

void process_queue_clear(PROCESS_QUEUE* queue)
{
    while(!process_queue_is_empty(queue))
    {
        process_queue_dequeue(queue);
    }
}

void process_queue_free(PROCESS_QUEUE* queue)
{
    process_queue_clear(queue);
    free(queue);
}
