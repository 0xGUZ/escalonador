#include "input_records.h"
#include "scheduler.h"
#include "view.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv)
{
    if(argc != 2)
    {
        fprintf(stderr, "Incorrect syntax for program. Do:\n");
        fprintf(stderr, "%s [input records file path]\n", argv[0]);
        return 1;
    }
    srand(time(NULL));
    input_records_initialize(argv[1]);
    scheduler_initialize();
    view_put_separator();
    view_show_until_input();
    while(!input_records_are_finished() || scheduler_has_active_processes())
    {
        scheduler_iterate();
        view_show_until_input();
    }
    view_show_until_input();
    printf("The records file ended and all processes are terminated.\n");
    return 0;
}
