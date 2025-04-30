#!/bin/bash

# The script will create a build directory, run CMake, and then build the project

# Check if the build directory exists
if [ -d "build" ]; then
    echo "Build directory already exists. Please remove it before running this script."
    exit 1
fi

# Create the build directory
mkdir build
cd build

# Run CMake
cmake ..

# Check if CMake was successful
if [ $? -ne 0 ]; then
    echo "CMake failed. Please check the output for errors."
    exit 1
fi

# Build the project
make

# Check if make was successful
if [ $? -ne 0 ]; then
    echo "Make failed. Please check the output for errors."
    exit 1
fi
