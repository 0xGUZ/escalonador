#include "queue.h"
#include "pcb.h"
#include <stdio.h>
#include <stdlib.h>

#define INITIAL_PRIORITY 1

// Malloca fila
Queue* createQueue() {
    Queue* ptr = (Queue*)malloc(sizeof(Queue));
    if(ptr == NULL){
        perror("Erro ao alocar memória em createQueue()");
        return NULL;
    }
    return ptr;
}

// Inicializa uma fila
void initializeQueue(Queue* q) {
    q->front = NULL;
    q->rear = NULL;
    q->count = 0;
}

// Inicializa multiplas filas
void initializeQueues(Queue** queues, int numberOfQueues) {
    for (int i = 0; i < numberOfQueues; i++) {
        initializeQueue(queues[i]);
    }
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

// Verifica se multiplas filas estão todas vazias 
int areQueuesEmpty(Queue** queues, int numberOfQueues) {
    for (int i = 0; i < numberOfQueues; i++) {
        if (!isQueueEmpty(queues[i])) {
            return 1;
        }
    }
    return 0;
}


// Imprime a fila toda
void printQueue(Queue* q) {
    Node* temp = q->front;
    printf("Fila: ");
    while (temp != NULL) {
        printf("\n[PID: %d, Prioridade: %d, Tempo CPU: %d, Tempo IO: %d, Tipo: %d, Tempo até IO: %d] -> ", temp->data.pid, temp->data.priority, temp->data.cpu_time, temp->data.io_time, temp->data.io_type, temp->data.time_until_io);
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

// Cria uma fila apartir da leitura de um arquivo
Queue* queueFromFile(const char* filepath) {
    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo em queueFromFile()");
        exit(EXIT_FAILURE);
    }

    Queue* queue = createQueue();
    initializeQueue(queue);

    int pid, cpu_time, io_time, io_type, time_until_io;

    // Ignora a primeira linha (são labels)
    fscanf(file, "%*s %*s %*s %*s %*s");

    // Lê cada linha do arquivo e adiciona à fila
    while (fscanf(file, "%d %d %d %d", &pid, &cpu_time, &io_time, &io_type, &time_until_io) == 3) {
        PCB pcb = createPCB(pid, INITIAL_PRIORITY, cpu_time, io_time, io_type, time_until_io);
        enqueue(queue, pcb);
    }

    fclose(file);
    return queue;
}

// Carrega a fila de um arquivo para uma fila passada por parametros
void loadInitialProcesses(Queue* q, const char* filepath) {
    Queue* loadedQueue = queueFromFile(filepath);
    while (!isQueueEmpty(loadedQueue)) {
        enqueue(q, dequeue(loadedQueue));
    }
    freeQueue(loadedQueue); 
}

// Tira todos os nós da fila e libera a memória
void freeQueue(Queue* q) {
    dequeueAll(q);
    free(q);
}

// Tira todos os nós de todas as filas e libera as memórias
void freeQueues(Queue** queues, int numberOfQueues) {
    for (int i = 0; i < numberOfQueues; i++) {
        freeQueue(queues[i]);
    }
}