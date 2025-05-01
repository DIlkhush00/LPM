#include "sort.h"
#include "process.h"
#include <assert.h>
#include <stdio.h>

void test_sort_pid() {
    ProcessInfo processes[3] = {
        {.pid = 3, .rss = 100},
        {.pid = 1, .rss = 200},
        {.pid = 2, .rss = 50}
    };
    
    sort_processes(processes, 3, SORT_PID);
    
    assert(processes[0].pid == 1);
    assert(processes[1].pid == 2);
    assert(processes[2].pid == 3);
    printf("✓ test_sort_pid passed\n");
}

void test_sort_mem() {
    ProcessInfo processes[3] = {
        {.pid = 1, .rss = 100},
        {.pid = 2, .rss = 200},
        {.pid = 3, .rss = 50}
    };
    
    sort_processes(processes, 3, SORT_MEM);
    
    assert(processes[0].rss == 200);
    assert(processes[1].rss == 100);
    assert(processes[2].rss == 50);
    printf("✓ test_sort_mem passed\n");
}