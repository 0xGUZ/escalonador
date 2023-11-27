#include <stdio.h>
#include <time.h>
#include "queue.h"
#include "pcb.h"

#define FILEPATH "input1.txt"
// TODO: FILEPATH como argumento da main??
// TODO: na real transformar tudo isso numa funcao pra poder fazer basicamente: escalona("input1.txt")

typedef enum {
    IO_DISCO,
    IO_FITA_MAGNETICA,
    IO_IMPRESSORA
} IOType;

// CONSTANTE
const int MAX_PROCESSOS = 10;
const int QUANTUM = 20;
const int DURACAO_IO_DISCO = 30; 
const int DURACAO_IO_FITA = 40;  
const int DURACAO_IO_IMPRESSORA = 50; 

// Metodos
void executeSchedulerIteration(Queue* highPriorityQueue, Queue* lowPriorityQueue, Queue* discoQueue, Queue* fitaQueue, Queue* impressoraQueue, int quantum);
void processIO(Queue* ioQueue, Queue* targetQueue);

// Main
int main() {
    // Cria as filas
    Queue* highPriorityQueue = createQueue();
    Queue* lowPriorityQueue = createQueue();
    Queue* discoQueue = createQueue();
    Queue* fitaQueue = createQueue();
    Queue* impressoraQueue = createQueue();

    // Array de filas pra uso posterior
    Queue* allQueues[] = {highPriorityQueue, lowPriorityQueue, discoQueue, fitaQueue, impressoraQueue};
    int numberOfQueues = sizeof(allQueues) / sizeof(allQueues[0]);

    // Inicializa todas as filas
    initializeQueues(allQueues, numberOfQueues);

    // Carrega os processos iniciais na fila de alta prioridade
    loadInitialProcesses(highPriorityQueue, FILEPATH);

    // Escalonador roda enquanto tem coisa nas filas
    while (!areQueuesEmpty(allQueues, numberOfQueues)) {
        executeSchedulerIteration(highPriorityQueue, lowPriorityQueue, discoQueue, fitaQueue, impressoraQueue, QUANTUM);
    }

    return 0;
}

// Iteracao do escalonador
void executeSchedulerIteration(Queue* highPriorityQueue, Queue* lowPriorityQueue, Queue* discoQueue, Queue* fitaQueue, Queue* impressoraQueue, int quantum) {
    PCB currentProcess;

    // Escolha um processo da fila de alta prioridade se tiver
    if (!isQueueEmpty(highPriorityQueue)) {
        currentProcess = dequeue(highPriorityQueue);
    } 
    // Nao tem alta entao ve se tem baixa
    else if (!isQueueEmpty(lowPriorityQueue)) {
        currentProcess = dequeue(lowPriorityQueue);
    } 
    // Nenhum processo disponível para execução
    else {
        return; 
    }

    // Simula um quantum
    currentProcess.cpu_time -= quantum;
    currentProcess.time_until_io -= quantum;
    processIO(discoQueue, lowPriorityQueue);
    processIO(fitaQueue, highPriorityQueue);
    processIO(impressoraQueue, highPriorityQueue);

    // Verifica o estado do processo após a execução
    if (currentProcess.cpu_time <= 0) {
        // Processo concluído, não precisa ser enfileirado novamente
    } else {
        // Verifica se precisa de I/O
        if (currentProcess.time_until_io <= 0) {
            switch (currentProcess.io_type) {
                case 0:
                    enqueue(discoQueue, currentProcess);
                    break;
                case 1:
                    enqueue(fitaQueue, currentProcess);
                    break;
                case 2:
                    enqueue(impressoraQueue, currentProcess);
                    break;
                default:
                    printf("Erro tipo de IO inválida para o processo de ID %d\n", currentProcess.pid);
                    break;
            }
            // e defina um temporizador para a duração da I/O (se necessário)
        } else {
            // Se não precisar de I/O e consumiu todo o quantum, vai para a fila de baixa prioridade
            enqueue(lowPriorityQueue, currentProcess);
        }
    }
}

// Roda o IO por um QUANTUM - PREMISSA AS FILAS DE IO SAO FIRST IN FIRST OUT
void processIO(Queue* ioQueue, Queue* targetQueue) {

    if (!isQueueEmpty(ioQueue)) {
        PCB process = ioQueue->front->data;
        process.io_time -= QUANTUM; 

        if (process.io_time <= 0) {
            dequeue(ioQueue, process); // Tira o processo do IO
            enqueue(targetQueue, process); // Processo completou IO, mova para a fila de destino
        } 
    }
}
// gcc main.c headers/pcb.c headers/queue.c -I headers -o main