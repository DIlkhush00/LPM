#ifndef UI_H
#define UI_H

#include "process.h"
#include "sort.h"

void ui_init();                      // Initialize ncurses UI
void ui_draw(ProcessInfo *processes, int count, SortOrder order);  // Draw table
void ui_cleanup();                   // Restore terminal

#endif