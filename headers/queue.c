#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

// Define as funções do header

// Inicializa a fila
void initializeQueue(Queue* q) {
    q->front = NULL;
    q->rear = NULL;
    q->count = 0;
}

// Adiciona um PCB ao final da fila
void enqueue(Queue* q, PCB process) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = process;
    newNode->next = NULL;

    if (isQueueEmpty(q)) {
        q->front = newNode;
    } else {
        q->rear->next = newNode;
    }
    q->rear = newNode;
    q->count++;
}

// Remove e retorna um PCB do início da fila
PCB dequeue(Queue* q) {
    PCB process;
    if (!isQueueEmpty(q)) {
        Node* temp = q->front;
        process = temp->data;
        q->front = q->front->next;
        if (q->front == NULL) {
            q->rear = NULL;
        }
        free(temp);
        q->count--;
    }
    return process;
}

// Verifica se a fila está vazia
int isQueueEmpty(Queue* q) {
    return (q->count == 0);
}

// Imprime a fila toda
void printQueue(Queue* q) {
    Node* temp = q->front;
    printf("Fila: ");
    while (temp != NULL) {
        printf("[PID: %d, Prioridade: %d] -> ", temp->data.pid, temp->data.priority);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Função para remover e liberar todos os elementos da fila
void dequeueAll(Queue* q) {
    while (!isQueueEmpty(q)) {
        dequeue(q);
    }
}