#include <stdio.h>

#define RUN_TEST(test) printf("Running " #test "... "); test(); printf("Passed\n")

void test_scan_processes();
void test_parse_status_file();
void test_sort_pid();
void test_sort_mem();
void test_is_numeric();

int main() {
    printf("Running tests...\n");
    
    RUN_TEST(test_scan_processes);
    RUN_TEST(test_parse_status_file);
    RUN_TEST(test_sort_pid);
    RUN_TEST(test_sort_mem);
    RUN_TEST(test_is_numeric);
    
    printf("All tests passed!\n");
    return 0;
}