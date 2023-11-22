#include <stdio.h>
#include <time.h>
#include "../headers/queue.c"
#include "../headers/pcb.c"

int main() {
    // VARIAVEIS
    int stop = 0;

    //seed random setada
    srand(time(NULL));

    // FILAS
    Queue highPriorityQueue;
    Queue mediumPriorityQueue;
    Queue lowPriorityQueue;
    Queue ioQueue;

    // Inicializa as filas
    initializeQueue(&highPriorityQueue);
    initializeQueue(&mediumPriorityQueue);
    initializeQueue(&lowPriorityQueue);
    initializeQueue(&ioQueue);

    // -X-X-X-X-X- ESCALONADOR -X-X-X-X-X-
    while (stop == 0) {
        PCB currentProcess;

        // Selecionar processo da fila de alta prioridade, depois média, depois baixa
        if (!isQueueEmpty(&highPriorityQueue)) {
            currentProcess = dequeue(&highPriorityQueue);
        } 
        
        else if (!isQueueEmpty(&mediumPriorityQueue)) {
            currentProcess = dequeue(&mediumPriorityQueue);
        } 
        
        else if (!isQueueEmpty(&lowPriorityQueue)) {
            currentProcess = dequeue(&lowPriorityQueue);
        }

        if (currentProcess.pid != -1) {
            // Simular execução do processo
            // Decidir o que fazer com o processo após a execução (terminou, I/O, etc.)
        }

        // Tratar processos de I/O
    }
}