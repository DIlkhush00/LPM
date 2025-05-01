#!/bin/bash

# Build and test script for Linux Process Monitor
set -e  # Exit immediately if any command fails

# Configuration
BUILD_DIR="build"
ENABLE_TESTS=true  # Set to false to skip tests

echo "=== Starting Build Process ==="

# Clean existing build
if [ -d "$BUILD_DIR" ]; then
    echo "Removing existing build directory..."
    rm -rf "$BUILD_DIR"
fi

# Create fresh build directory
echo "Creating build directory..."
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR" || exit 1

# Run CMake configuration
echo "Running CMake configuration..."
cmake .. -DENABLE_TESTS=${ENABLE_TESTS}

# Build the project
echo "Building project..."
make

# Run tests if enabled
if [ "$ENABLE_TESTS" = true ]; then
    echo "=== Running Tests ==="
    ctest --output-on-failure
    
    if [ $? -eq 0 ]; then
        echo "✓ All tests passed successfully"
    else
        echo "✗ Some tests failed"
        exit 1
    fi
else
    echo "Test execution skipped (ENABLE_TESTS=false)"
fi

echo ""
echo "=== Build Successful ==="
echo "Run the program with: ./build/lpm"