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

void list_processes();

#endif