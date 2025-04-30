#ifndef PROCESS_H
#define PROCESS_H

#include <sys/types.h>

typedef struct {
    pid_t pid;
    char name[256];
    char state;
    long rss; // Memory in KB
    uid_t uid;
    char username[32];
} ProcessInfo;

int scan_processes(ProcessInfo *processes, int max);
void parse_status_file(pid_t pid, ProcessInfo *proc);

#endif