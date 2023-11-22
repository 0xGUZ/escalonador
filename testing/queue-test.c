#include "../headers/queue.h"
#include "../headers/pcb.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    // Cria uma fila
    Queue* myQueue = (Queue*)malloc(sizeof(Queue));
    initializeQueue(myQueue);

    // Adiciona alguns PCBs fictícios à fila
    for (int i = 0; i < 5; i++) {
        PCB pcb = createRandomPCB();
        enqueue(myQueue, pcb);
    }

    // Imprime o conteúdo da fila
    printf("Conteudo da fila apos enfileirar PCBs:\n");
    printQueue(myQueue);

    // Remove um PCB da fila e imprime seu PID
    PCB removedPCB = dequeue(myQueue);
    printf("\nPCB removido: PID = %d, Prioridade = %d\n", removedPCB.pid, removedPCB.priority);

    // Imprime o conteúdo da fila após a remoção
    printf("\nConteudo da fila apos desenfileirar um PCB:\n");
    printQueue(myQueue);

    // Remove todos os PCBs restantes
    dequeueAll(myQueue);

    // Verifica se a fila está vazia
    printf("\nConteudo da fila apos remover todos os PCBs:\n");
    printQueue(myQueue);

    // Libera a memória alocada para a fila
    free(myQueue);

    return 0;
}
