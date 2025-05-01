cmake_minimum_required(VERSION 3.1)

# Test Configuration
set(TEST_SOURCES
    test_main.c
    test_process.c
    test_sort.c
    test_utils.c
)

set(TEST_LIBS
    ${CURSES_LIBRARIES}
)

set(SOURCE_DEPS
    ../src/process.c
    ../src/sort.c
    ../src/utils.c
)

#####
# Main Test Executable
#####
add_executable(lpm_tests
    ${TEST_SOURCES}
    ${SOURCE_DEPS}
)

target_link_libraries(lpm_tests ${TEST_LIBS})

#####
# CTest Configuration
#####
enable_testing()

# Main aggregated test
add_test(NAME lpm_tests_all COMMAND lpm_tests)

# Add memory check if available
find_program(MEMORYCHECK_COMMAND valgrind)
if(MEMORYCHECK_COMMAND)
    add_test(NAME lpm_tests_memcheck COMMAND valgrind --leak-check=full --error-exitcode=1 ./lpm_tests)
endif()

# Add test properties
set_tests_properties(lpm_tests_all PROPERTIES
    TIMEOUT 30
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)