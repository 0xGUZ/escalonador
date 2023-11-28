#ifndef INPUT_RECORDS_H
#define INPUT_RECORDS_H

typedef struct
{
    unsigned pid;
    unsigned starting_time;
    unsigned run_time;
}
INPUT_RECORD;

void input_records_initialize(char* file_path);

int input_records_are_finished(void);

void input_records_read_next(INPUT_RECORD* out_input_record);

void input_records_discard_next(void);

void input_records_close(void);

#endif
