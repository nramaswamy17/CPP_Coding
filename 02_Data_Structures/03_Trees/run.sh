#!/bin/bash

# Check if a filename was provided
if [ $# -eq 0 ]; then
    echo "Usage: bash run.sh <cpp_file>"
    exit 1
fi

cpp_file=$1
base_name="${cpp_file%.cpp}"
out_file="${base_name}_out"

# Compile the C++ file
g++ -std=c++17 "$cpp_file" -o "$out_file"

# Check if compilation was successful
if [ $? -eq 0 ]; then
    # Run the compiled program
    ./"$out_file"
else
    echo "Compilation failed"
    exit 1
fi