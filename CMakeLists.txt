cmake_minimum_required(VERSION 3.1...3.29.5)

#####
## Project
#####
project(lpm VERSION 1.0.0 LANGUAGES C)

######
## Set C Standard
######

set(CMAKE_C_STANDARD 99)

# Find the ncurses library
find_package(Curses REQUIRED)

#######
## Include Directories
#######

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CURSES_INCLUDE_DIRS}
)

#######
# Testing Setup
#######
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests")
    message(STATUS "Enabling tests")
    enable_testing()
    add_subdirectory(tests)
else()
    message(WARNING "Tests directory not found - skipping tests")
endif()


# -----------------
# Add the executable
# -----------------

add_executable(
    ${CMAKE_PROJECT_NAME}
    src/main.c
    src/process.c
    src/utils.c
    src/ui.c
    src/sort.c
)

target_link_libraries(${CMAKE_PROJECT_NAME} ${CURSES_LIBRARIES})