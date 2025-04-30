#include "process.h"
#include "sort.h"
#include "ui.h"
#include <ncurses.h>
#include <unistd.h>

int main() {
    ProcessInfo processes[1024];
    SortOrder order = SORT_PID;
    int should_quit = 0;
    
    ui_init();
    
    while (!should_quit) {
        int count = scan_processes(processes, 1024);
        sort_processes(processes, count, order);
        
        ui_draw(processes, count, order);
        
        int ch;
        while ((ch = getch()) != ERR) {
            if (ch == 'm') order = SORT_MEM;
            else if (ch == 'p') order = SORT_PID;
            else if (ch == 'q') should_quit = 1;
        }
        
        usleep(50000);
    }
    
    ui_cleanup();
    return 0;
}