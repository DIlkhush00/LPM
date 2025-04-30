cmake_minimum_required(VERSION 3.1...3.29.5)

#####
## Project
#####
project(lpm VERSION 1.0.0 LANGUAGES C)

######
## Set C Standard
######

set(CMAKE_C_STANDARD 99)

#######
## Include Directories
#######

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# -----------------
# Add the executable
# -----------------

add_executable(
    ${CMAKE_PROJECT_NAME}
    src/main.c
)