#include "../headers/queue.h"
#include "../headers/pcb.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    // Cria uma fila
    Queue* fila1 = createQueue();
    initializeQueue(fila1);

    // Adiciona alguns PCBs fictícios à fila
    for (int i = 0; i < 5; i++) {
        PCB pcb = createRandomPCB();
        enqueue(fila1, pcb);
    }

    // Imprime o conteúdo da fila
    printf("Conteudo da fila apos enfileirar PCBs:\n");
    printQueue(fila1);

    // Remove um PCB da fila e imprime seu PID
    PCB removedPCB = dequeue(fila1);
    printf("\nPCB removido: PID = %d, Prioridade = %d\n", removedPCB.pid, removedPCB.priority);

    // Imprime o conteúdo da fila após a remoção
    printf("\nConteudo da fila apos desenfileirar um PCB:\n");
    printQueue(fila1);

    // Remove todos os PCBs restantes
    dequeueAll(fila1);

    // Verifica se a fila está vazia
    printf("\nConteudo da fila apos remover todos os PCBs:\n");
    printQueue(fila1);

    printf("\nFila do arquivo: \n");
    Queue* fila2 = queueFromFile("input.txt");
    printQueue(fila2);

    // Libera a memória alocada para a fila
    freeQueue(fila1);
    freeQueue(fila2);

    return 0;
}
