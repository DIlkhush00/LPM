#include "process.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <pwd.h>

static void parse_status_file(pid_t pid, ProcessInfo *proc) {
    char path[256];
    FILE *fp;
    char line[256];

    snprintf(path, sizeof(path), "/proc/%d/status", pid);
    fp = fopen(path, "r");
    if (!fp) return;

    while (fgets(line, sizeof(line), fp)) {
        if (sscanf(line, "Name:\t%s", proc->name) == 1) continue;
        else if (sscanf(line, "State:\t%c", &proc->state) == 1) continue;
        else if (sscanf(line, "VmRSS:\t%ld kB", &proc->rss) == 1) continue;
        else if (sscanf(line, "Uid:\t%d", &proc->uid) == 1) {
            struct passwd *pw = getpwuid(proc->uid);
            if (pw) snprintf(proc->username, sizeof(proc->username), "%s", pw->pw_name);
            else snprintf(proc->username, sizeof(proc->username), "?");
        }
    }
    fclose(fp);
}

void list_processes() {
    DIR *dir = opendir("/proc");
    if (!dir) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    printf("%-8s %-8s %-6s %-8s %s\n", "PID", "USER", "STATE", "MEM(KB)", "COMMAND");
    
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR && is_numeric(entry->d_name)) {
            ProcessInfo proc = {0};
            proc.pid = atoi(entry->d_name);
            parse_status_file(proc.pid, &proc);

            // Fallback to cmdline if name missing (kernel threads)
            if (proc.name[0] == '\0') {
                FILE *fp;
                char cmdline[256];
                snprintf(cmdline, sizeof(cmdline), "/proc/%d/cmdline", proc.pid);
                fp = fopen(cmdline, "r");
                if (fp) {
                    if (fgets(cmdline, sizeof(cmdline), fp)) {
                        for (char *p = cmdline; *p; p++) if (*p == '\0') *p = ' ';
                        snprintf(proc.name, sizeof(proc.name), "%s", cmdline);
                    }
                    fclose(fp);
                }
            }

            printf("%-8d %-8s %-6c %-8ld %s\n", 
                   proc.pid, proc.username, proc.state, proc.rss, proc.name);
        }
    }
    closedir(dir);
}