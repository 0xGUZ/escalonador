#include <stdio.h>
#include <time.h>
#include "../headers/queue.c"
#include "../headers/pcb.c"

#define FILEPATH "../input.txt"

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

    }
}