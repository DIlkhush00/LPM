#!/bin/bash

# The script will create a build directory, run CMake, and then build the project

# Check if the build directory exists
if [ -d "build" ]; then
    echo "Build directory already exists."

    # remove the existing build directory
    echo "Removing existing build directory..."
    rm -rf build
    echo "Existing build directory removed."

    # Check if the removal was successful
    if [ $? -ne 0 ]; then
        echo "Failed to remove existing build directory. Please check permissions."
        exit 1
    fi
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
