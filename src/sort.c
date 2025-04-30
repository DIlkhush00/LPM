#include "sort.h"
#include <stdlib.h>

// Compare PIDs (ascending)
static int compare_pid(const void *a, const void *b) {
    return ((ProcessInfo*)a)->pid - ((ProcessInfo*)b)->pid;
}

// Compare memory (descending)
static int compare_mem(const void *a, const void *b) {
    return ((ProcessInfo*)b)->rss - ((ProcessInfo*)a)->rss;
}

void sort_processes(ProcessInfo *processes, int count, SortOrder order) {
    switch (order) {
        case SORT_PID: qsort(processes, count, sizeof(ProcessInfo), compare_pid); break;
        case SORT_MEM: qsort(processes, count, sizeof(ProcessInfo), compare_mem); break;
    }
}