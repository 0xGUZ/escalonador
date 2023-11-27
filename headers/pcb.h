#ifndef PCB_H
#define PCB_H

// PCB é a identidade de um processo, guarda todas as infos essenciais dele
// Definição da estrutura PCB
typedef struct {
    int pid;                // Identificador do processo
    enum {NEW, READY, RUNNING, WAITING, TERMINATED} state; // Estado do processo
    int priority;           // Prioridade do processo
    int cpu_time;           // Tempo total de CPU usado
    int io_time;            // Tempo total gasto em operações de I/O
    int io_type;            // Tipo de operação de I/O (disco, fita ou impressora)
    int time_until_io;
} PCB;

PCB createPCB(int pid, int priority, int cpu_time, int io_time, int io_type, int time_until_io);
PCB createRandomPCB();
void createRandomTable(int id, int numProcesses);

#endif