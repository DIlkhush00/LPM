#include "process.h"
#include "utils.h"
#include <assert.h>
#include <unistd.h>
#include <stdio.h>

void test_scan_processes() {
    ProcessInfo processes[10];
    int count = scan_processes(processes, 10);
    
    assert(count > 0);
    assert(processes[0].pid == 1);
    assert(processes[0].state != '?');
    printf("✓ test_scan_processes passed\n");
}

void test_parse_status_file() {
    ProcessInfo proc = {0};
    proc.pid = getpid();
    
    parse_status_file(proc.pid, &proc);
    
    assert(proc.state != '?');
    assert(proc.rss > 0);
    printf("✓ test_parse_status_file passed\n");
}