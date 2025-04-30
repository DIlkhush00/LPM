#include "ui.h"
#include "sort.h"
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h> // for usleep

void ui_init() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    start_color();
    use_default_colors();
    init_pair(1, COLOR_RED, -1);
    init_pair(2, COLOR_GREEN, -1);
    timeout(50); // Non-blocking input with 50ms timeout
}

void ui_draw(ProcessInfo *processes, int count, SortOrder order) {
    static int scroll_offset = 0;
    int ch;

    // Process input immediately
    while ((ch = getch()) != ERR) {
        switch (ch) {
            case KEY_UP:   if (scroll_offset > 0) scroll_offset--; break;
            case KEY_DOWN: if (scroll_offset < count - LINES + 2) scroll_offset++; break;
            case 'q': return; // Exit signal
        }
    }

    clear();
    
    // Header
    attron(A_BOLD);
    mvprintw(0, 0, "%-8s %-12s %-6s %-10s %s (Sort: %s)", 
             "PID", "USER", "STATE", "MEM(KB)", "COMMAND",
             order == SORT_PID ? "PID" : "MEM");
    attroff(A_BOLD);

    // Visible processes
    int max_rows = LINES - 2;
    for (int i = 0; i < max_rows && (i + scroll_offset) < count; i++) {
        ProcessInfo *proc = &processes[i + scroll_offset];
        
        // Highlighting
        if (proc->rss > 100000) attron(COLOR_PAIR(1));
        else if (proc->state == 'R') attron(COLOR_PAIR(2));

        mvprintw(i + 1, 0, "%-8d %-12s %-6c %-10ld %.*s", 
                proc->pid, 
                proc->username, 
                proc->state, 
                proc->rss,
                COLS - 36, // Prevent overflow
                proc->name);
                
        attroff(COLOR_PAIR(1) | COLOR_PAIR(2));
    }

    // Footer
    attron(A_REVERSE);
    mvprintw(LINES - 1, 0, "Press 'q': quit | 'm': sort by MEM | 'p': sort by PID | %d/%d", scroll_offset + 1, count);
    clrtoeol();
    attroff(A_REVERSE);
    
    refresh();
}

void ui_cleanup() {
    endwin();
}