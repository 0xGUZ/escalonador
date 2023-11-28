#include "io_type.h"

const IO_TYPE IO_TYPE_TYPES[IO_TYPE_NUMBER_OF_TYPES] = {DISK, MAGNETIC_TAPE, PRINTER};

const char* io_type_name(IO_TYPE io_type)
{
    switch(io_type)
    {
        case DISK:              return "Disk";
        case MAGNETIC_TAPE:     return "Magnetic tape";
        case PRINTER:           return "Printer";
    }
    return "Undefined";
}

unsigned io_type_duration(IO_TYPE io_type)
{
    switch(io_type)
    {
        case DISK:              return 3;
        case MAGNETIC_TAPE:     return 2;
        case PRINTER:           return 5;
    }
    return 0;
}

unsigned io_type_chance_to_occur(IO_TYPE io_type)
{
    switch(io_type)
    {
        case DISK:              return 10;
        case MAGNETIC_TAPE:     return 5;
        case PRINTER:           return 3;
    }
    return 0;
}

unsigned io_type_priority_for_process_after_io_completion(IO_TYPE io_type)
{
    switch(io_type)
    {
        case DISK:              return 1;
        case MAGNETIC_TAPE:     return 0;
        case PRINTER:           return 0;
    }
    return 0;
}
