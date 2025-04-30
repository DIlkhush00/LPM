#ifndef SORT_H
#define SORT_H

#include "process.h"

typedef enum {
    SORT_PID,
    SORT_MEM
} SortOrder;

void sort_processes(ProcessInfo *processes, int count, SortOrder order);

#endif