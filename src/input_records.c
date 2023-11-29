#include "input_records.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

INPUT_RECORD input_records_next_record;
int input_records_has_next_record;

FILE* input_records_input_stream;

void input_records_initialize(char* file_path)
{
    input_records_input_stream = fopen(file_path, "r");
    if(input_records_input_stream == NULL)
    {
        fprintf(stderr, "Error: Input file could not be opened.\n");
        exit(2);
    }
    input_records_has_next_record = 0;
}

int input_records_are_finished(void)
{
    int character;
    if(input_records_has_next_record) return 0;
    character = fgetc(input_records_input_stream);
    while(isspace((char) character))
    {
        character = fgetc(input_records_input_stream);
    }
    if(feof(input_records_input_stream)) return 1;
    ungetc(character, input_records_input_stream);
    return 0;
}

void input_records_read_next(INPUT_RECORD* out_input_record)
{
    int could_read_count;
    if(!input_records_has_next_record)
    {
        could_read_count = fscanf(input_records_input_stream, " %u %u %u",
            &input_records_next_record.pid, &input_records_next_record.starting_time, &input_records_next_record.run_time);
        if(could_read_count < 3)
        {
            fprintf(stderr, "Error: Could not read record from input file.\n");
            exit(3);
        }
    }
    *out_input_record = input_records_next_record;
    input_records_has_next_record = 1;
}

void input_records_advance(void)
{
    input_records_has_next_record = 0;
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
