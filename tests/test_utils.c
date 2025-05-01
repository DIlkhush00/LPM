#include "utils.h"
#include <assert.h>
#include <stdio.h>

void test_is_numeric() {
    assert(is_numeric("123") == 1);
    assert(is_numeric("abc") == 0);
    assert(is_numeric("123abc") == 0);
    assert(is_numeric("") == 0);
    printf("✓ test_is_numeric passed\n");
}