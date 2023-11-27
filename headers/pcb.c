#include "pcb.h"
#include <stdlib.h>
#include <stdio.h>

// Função para criar um novo PCB
PCB createPCB(int pid, int priority, int cpu_time, int io_time, int io_type, int time_until_io) {
    PCB newPCB;
    newPCB.pid = pid;
    newPCB.state = NEW; // Estado inicial é novo
    newPCB.priority = priority;
    newPCB.cpu_time = cpu_time;
    newPCB.io_time = io_time;
    newPCB.io_type = io_type;
    newPCB.time_until_io = time_until_io;
    return newPCB;
}

// Função para criar um novo PCB com valores aleatórios 
// Respeita as premissas estabelidas

PCB createRandomPCB() {
    static int pid = 1; // PID inicial e incrementa para cada PCB criado

    int priority = (rand() % 5) + 1; // Prioridade entre 1 e 5
    int cpu_time = (rand() % 91) + 10; // Tempo de CPU entre 10 e 100
    int io_time = (rand() % 91) + 10; // Tempo de I/O entre 10 e 100
    int io_type = (rand() % 3); // Tipo de IO
    int time_until_io = (rand() % cpu_time) + 1; // Tempo de IO acontece durante execucao

    PCB randomPCB = createPCB(pid, priority, cpu_time, io_time, io_type, time_until_io);
    pid++;

    return randomPCB;
}

// Usa a função createRandomPCB pra criar uma tabela de input

void createRandomTable(int id, int numProcesses) {
    char filename[50];
    sprintf(filename, "input%d.txt", id); // Cria o nome do arquivo com o ID fornecido

    FILE *file = fopen(filename, "w"); // Abre o arquivo para escrita
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Escreve o cabeçalho no arquivo
    fprintf(file, "PID CPU_time IO_time IO_type Time_until_IO\n");

    // Gera e escreve os processos aleatórios no arquivo
    for (int i = 0; i < numProcesses; i++) {
        PCB randomPCB = createRandomPCB();
        fprintf(file, "%d %d %d %d %d\n", randomPCB.pid, randomPCB.cpu_time, randomPCB.io_time, randomPCB.io_type, randomPCB.time_until_io);
    }

    fclose(file); // Fecha o arquivo
}