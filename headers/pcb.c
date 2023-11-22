#include "pcb.h"
#include <stdlib.h>
#include <time.h>


// Função para criar um novo PCB
PCB createPCB(int pid, int priority, int cpu_time, int io_time) {
    PCB newPCB;
    newPCB.pid = pid;
    newPCB.priority = priority;
    newPCB.cpu_time = cpu_time;
    newPCB.io_time = io_time;
    newPCB.state = NEW; // Estado inicial é novo
    // Se criar novos campos mudar aqui
    return newPCB;
}

// Função para criar um novo PCB com valores aleatórios 
// Respeita as premissas estabelidas

PCB createRandomPCB() {
    static int pid = 1; // PID inicial e incrementa para cada PCB criado
    srand(time(NULL) + pid); // Inicializa a semente do gerador de números aleatórios

    int priority = (rand() % 5) + 1; // Prioridade entre 1 e 5
    int cpu_time = (rand() % 91) + 10; // Tempo de CPU entre 10 e 100
    int io_time = (rand() % 91) + 10; // Tempo de I/O entre 10 e 100

    PCB randomPCB = createPCB(pid, priority, cpu_time, io_time);
    pid++;

    return randomPCB;
}