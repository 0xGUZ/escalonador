#include <stdio.h>
#include <stdlib.h>
#include "pcb.h"
#include "queue.h"

int main() {
    int tableID = 1;
    int numProcesses = 10;
    createRandomTable(tableID, numProcesses);
    return 0;
}

// gcc generate_table.c headers/pcb.c headers/queue.c -I headers -o generate_table  