# Escalonador
Simulador de um escalonador round-robin (circular) com feedback em C.

## Premissas

* Prioridade: Vamos assumir que a prioridade pode variar de 1 a 5, onde 1 é a mais alta prioridade e 5 é a mais baixa.

* Tempo de CPU: O tempo de CPU pode variar, por exemplo, de 10 a 100 unidades de tempo.

* Tempo de I/O: O tempo de I/O também pode variar de 10 a 100 unidades de tempo.

* Quantum: O quantum pode ser fixo, por exemplo, 20 unidades de tempo, ou também pode variar dentro de um intervalo definido.

## Funções importantes 

### Fila

A struct Queue guarda: ponteiro para o Node de início e fim da fila, além disso o número de elementos que tem dentro dessa. A fila é composta de Nodes que guardam ponteiro para o próximo, e o PCB dentro de data.

* void printQueue(Queue* q); 
Printa a fila na ordem apartir do nó q, printando as propriedades de cada nó.

* Queue* queueFromFile(const char* filepath);
Lê arquivo de texto ignora a primeira linha, para cada linha seguinte cria um processo com as propriedades atribuídas na seguinte ordem: (PID, CPU_time, IO_time).

* void loadInitialProcesses(Queue* highPriorityQueue, const char* filepath);
Carrega a fila do arquivo na fila de alta prioridade.

* void freeQueue(Queue* q);
Tira todo mundo da fila depois da free no nó cabeça.

### PCB

A struct PCB tem as propriedades pid (ID do processo), state (Estado: "NOVO", "PRONTO", etc...), Priority (Prioridade do processo), cpu_time (Tempo pra execução), io_time (Tempo pra fila de io), io_type (Tipo de io)

* PCB createPCB(int pid, int priority, int cpu_time, int io_time);
Cria uma instância da struct PCB com os parâmetros inseridos.

* PCB createRandomPCB();
Cria uma instância da struct PCB com parâmetros aleatórios dentro de certas restrições.