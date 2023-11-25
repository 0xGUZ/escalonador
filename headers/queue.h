#ifndef QUEUE_H
#define QUEUE_H

#include "pcb.h"  // Importa o PCB

// Estrutura do nó da fila
typedef struct Node {
    PCB data;            // Dados do PCB
    struct Node* next;   // Ponteiro para o próximo nó
} Node;

// Estrutura da fila
typedef struct {
    Node* front;         // Ponteiro para o início da fila
    Node* rear;          // Ponteiro para o final da fila
    int count;           // Contador para o número de elementos na fila
} Queue;

// Funções para manipulação da fila
Queue* createQueue();
void initializeQueue(Queue* queue);
void initializeQueues(Queue** queues, int numberOfQueues);
void enqueue(Queue* queue, PCB process);
PCB dequeue(Queue* queue);
int isQueueEmpty(Queue* queue);
int areQueuesEmpty(Queue** queues, int numberOfQueues);
void printQueue(Queue* queue);
void dequeueAll(Queue* queue);
Queue* queueFromFile(const char* filepath);
void loadInitialProcesses(Queue* highPriorityQueue, const char* filepath);
void freeQueue(Queue* queue);
void freeQueues(Queue** queues, int numberOfQueues);

#endif // QUEUE_H
