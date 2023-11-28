#include "input_records.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

INPUT_RECORD current_input_record;
int has_current_input_record;

FILE* input_records_input_stream;

void input_records_initialize(char* file_path)
{
    input_records_input_stream = fopen(file_path, "r");
    if(input_records_input_stream == NULL)
    {
        fprintf(stderr, "Error: Input file could not be opened.\n");
        exit(2);
    }
    has_current_input_record = 0;
}

int input_records_are_finished(void)
{
    int character;
    while(isspace((char) (character = fgetc(input_records_input_stream))));
    if(character == EOF) return 1;
    ungetc(character, input_records_input_stream);
    return 0;
}

void input_records_read_next(INPUT_RECORD* out_input_record)
{
    int could_read_count;
    if(has_current_input_record)
    {
        *out_input_record = current_input_record;
        return;
    }
    could_read_count = fscanf(input_records_input_stream, " %u %u %u",
            &out_input_record->pid, &out_input_record->starting_time, &out_input_record->run_time);
    if(could_read_count < 2)
    {
        fprintf(stderr, "Error: Could not read record from input file.\n");
        exit(3);
    }
    has_current_input_record = 1;
}

void input_records_discard_next(void)
{
    has_current_input_record = 0;
}

void input_records_close(void)
{
    int could_not_close = fclose(input_records_input_stream);
    if(could_not_close)
    {
        fprintf(stderr, "Error: Could not close input file.\n");
        exit(4);
    }
}
