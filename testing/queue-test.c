#include <stdio.h>
#include <stdlib.h>
#include "../headers/queue.h"

int main() {
    Queue* highPriority = malloc(sizeof(Queue));
    initializeQueue(highPriority);

    // Criando e enfileirando alguns processos fictícios
    for (int i = 0; i < 5; i++) {
        PCB process;
        process.pid = i;
        process.priority = 2;  // alta prioridade
        enqueue(highPriority, process);
    }
    
    printQueue(highPriority);
    dequeueAll(highPriority);

    return 0;
}
