#include "../headers/pcb.h"
#include "../headers/queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL)); // Inicializa a semente do gerador de números aleatórios

    // Cria uma fila para os PCBs
    Queue* pcbQueue = (Queue*)malloc(sizeof(Queue));
    initializeQueue(pcbQueue);

    // Cria e enfileira alguns PCBs com valores definidos
    for (int i = 0; i < 3; i++) {
        PCB definedPCB = createPCB(i, i+1, 50, 30); // Criando PCBs com valores definidos
        enqueue(pcbQueue, definedPCB);
    }

    // Cria e enfileira alguns PCBs com valores aleatórios
    for (int i = 0; i < 3; i++) {
        PCB randomPCB = createRandomPCB(); // Criando PCBs com valores aleatórios
        enqueue(pcbQueue, randomPCB);
    }

    // Imprime e desenfileira todos os PCBs
    printf("Desenfileirando PCBs:\n");
    while (!isQueueEmpty(pcbQueue)) {
        PCB pcb = dequeue(pcbQueue);
        printf("PCB PID: %d, Prioridade: %d, Tempo de CPU: %d, Tempo de I/O: %d\n",pcb.pid, pcb.priority, pcb.cpu_time, pcb.io_time);
    }

    // Libera a memória alocada para a fila
    free(pcbQueue);

    return 0;
}
