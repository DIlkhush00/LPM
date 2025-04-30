#include "process.h"
#include "utils.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <pwd.h>
#include <unistd.h> 

#define MAX_PROCESSES 1024

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
    // Ncurses setup
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    scrollok(stdscr, TRUE);
    idlok(stdscr, TRUE);

    ProcessInfo processes[MAX_PROCESSES];
    int process_count = 0;

    while (1) {
        clear(); 
        process_count = 0;

        // Scan /proc
        DIR *dir = opendir("/proc");
        if (!dir) {
            endwin();
            perror("opendir");
            exit(EXIT_FAILURE);
        }

        // Read all processes
        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL && process_count < MAX_PROCESSES) {
            if (entry->d_type == DT_DIR && is_numeric(entry->d_name)) {
                ProcessInfo *proc = &processes[process_count++];
                proc->pid = atoi(entry->d_name);
                parse_status_file(proc->pid, proc);

                // Fallback to cmdline
                if (proc->name[0] == '\0') {
                    char cmdline[256];
                    FILE *fp = fopen(cmdline, "r");
                    if (fp) {
                        if (fgets(cmdline, sizeof(cmdline), fp)) {
                            for (char *p = cmdline; *p; p++) if (*p == '\0') *p = ' ';
                            snprintf(proc->name, sizeof(proc->name), "%s", cmdline);
                        }
                        fclose(fp);
                    }
                }
            }
        }
        closedir(dir);

        // Print header
        mvprintw(0, 0, "%-8s %-12s %-6s %-10s %s", "PID", "USER", "STATE", "MEM(KB)", "COMMAND");

        // Print processes
        for (int i = 0; i < process_count; i++) {
            ProcessInfo *proc = &processes[i];
            mvprintw(i + 1, 0, "%-8d %-12s %-6c %-10ld %s", 
                    proc->pid, 
                    proc->username, 
                    proc->state, 
                    proc->rss, 
                    proc->name);
        }

        // Footer instructions
        mvprintw(LINES - 1, 0, "Press 'q' to quit | Processes: %d", process_count);
        refresh();

        napms(50);  // Small delay to reduce CPU usage
        int ch = getch();
        if (ch == 'q') break;
    }

    endwin();
}