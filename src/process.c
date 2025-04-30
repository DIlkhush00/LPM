#include "process.h"
#include "utils.h"
#include <dirent.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Parse /proc/[PID]/status and populate ProcessInfo
void parse_status_file(pid_t pid, ProcessInfo *proc) {
    char path[256];
    snprintf(path, sizeof(path), "/proc/%d/status", pid);
    FILE *fp = fopen(path, "r");
    if (!fp) {
        proc->state = '?';
        proc->rss = 0;
        proc->uid = 0;
        strcpy(proc->username, "?");
        return;
    }

    char line[256];
    int uid_processed = 0;
    
    while (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, "Name:", 5) == 0) {
            sscanf(line + 6, "%255s", proc->name);
        }
        else if (strncmp(line, "State:", 6) == 0) {
            sscanf(line + 7, "%c", &proc->state);
        }
        else if (strncmp(line, "VmRSS:", 6) == 0) {
            sscanf(line + 6, "%ld", &proc->rss);
        }
        else if (!uid_processed && strncmp(line, "Uid:", 4) == 0) {
            uid_processed = 1;
            sscanf(line + 5, "%d", &proc->uid);
            
            struct passwd *pw = getpwuid(proc->uid);
            if (pw) {
                strncpy(proc->username, pw->pw_name, sizeof(proc->username) - 1);
                proc->username[sizeof(proc->username) - 1] = '\0';
            } else {
                strcpy(proc->username, "?");
            }
        }
    }
    fclose(fp);

    // Ensure null-termination
    proc->name[sizeof(proc->name) - 1] = '\0';
    proc->username[sizeof(proc->username) - 1] = '\0';
}

// Read command line from /proc/[PID]/cmdline (fallback for kernel threads)
void parse_cmdline(pid_t pid, ProcessInfo *proc) {
    char path[256];
    FILE *fp;
    char cmdline[256] = {0};

    snprintf(path, sizeof(path), "/proc/%d/cmdline", pid);
    fp = fopen(path, "r");
    if (!fp) return;

    if (fgets(cmdline, sizeof(cmdline), fp)) {
        for (char *p = cmdline; *p; p++) {
            if (*p == '\0') *p = ' ';
        }
        snprintf(proc->name, sizeof(proc->name), "%s", cmdline);
    }
    fclose(fp);
}

// Scan /proc and populate processes array
int scan_processes(ProcessInfo *processes, int max_processes) {
    DIR *dir;
    struct dirent *entry;
    int count = 0;

    dir = opendir("/proc");
    if (!dir) {
        perror("opendir");
        return -1;
    }

    while ((entry = readdir(dir)) != NULL && count < max_processes) {
        if (entry->d_type == DT_DIR && is_numeric(entry->d_name)) {
            pid_t pid = atoi(entry->d_name);
            ProcessInfo *proc = &processes[count++];
            proc->pid = pid;
            
            // Initialize defaults
            proc->name[0] = '\0';
            proc->state = '?';
            proc->rss = 0;
            proc->uid = 0;
            strcpy(proc->username, "?");

            parse_status_file(pid, proc);
            
            // Kernel threads often lack Name in status; use cmdline
            if (proc->name[0] == '\0') {
                parse_cmdline(pid, proc);
            }
        }
    }
    closedir(dir);
    return count;
}