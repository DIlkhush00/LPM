#include "utils.h"
#include <ctype.h>

int is_numeric(const char *str) {
    if (!str || !*str) return 0;
    
    while (*str) {
        if (!isdigit(*str)) return 0;
        str++;
    }
    return 1;
}