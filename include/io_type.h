#ifndef IO_TYPE_H
#define IO_TYPE_H

#define IO_TYPE_NUMBER_OF_TYPES 3

typedef enum
{
    DISK,
    MAGNETIC_TAPE,
    PRINTER
}
IO_TYPE;

extern const IO_TYPE IO_TYPE_TYPES[IO_TYPE_NUMBER_OF_TYPES];

const char* io_type_name(IO_TYPE io_type);
unsigned io_type_duration(IO_TYPE io_type);
unsigned io_type_chance_to_occur(IO_TYPE io_type);
unsigned io_type_priority_for_process_after_io_completion(IO_TYPE io_type);

#endif
