# Escalonador
Simulador de um escalonador round-robin (circular) com feedback em C.

## Premissas

* Prioridade: Vamos assumir que a prioridade pode variar de 1 a 5, onde 1 é a mais alta prioridade e 5 é a mais baixa.

* Tempo de CPU: O tempo de CPU pode variar, por exemplo, de 10 a 100 unidades de tempo.

* Tempo de I/O: O tempo de I/O também pode variar de 10 a 100 unidades de tempo.

* Quantum: O quantum pode ser fixo, por exemplo, 20 unidades de tempo, ou também pode variar dentro de um intervalo definido.