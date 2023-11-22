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

// Declarações de funções para manipulação da fila
void initializeQueue(Queue* q);
void enqueue(Queue* q, PCB process);
PCB dequeue(Queue* q);
int isQueueEmpty(Queue* q);
void printQueue(Queue* q);
void dequeueAll(Queue* q);

#endif // QUEUE_H
