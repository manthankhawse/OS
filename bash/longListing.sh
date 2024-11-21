#!/bin/bash
# Script to list files and count them

directory=${1:-.}  # Default to current directory if no argument is given

# Long listing
echo "Long listing of files in $directory:"
ls -l "$directory"

# Counting files
file_count=$(find "$directory" -type f | wc -l)
echo "Total number of files: $file_count"

# Copying result to another file
echo "Long listing of files in $directory:" > result.txt
ls -l "$directory" >> result.txt
echo "Total number of files: $file_count" >> result.txt
echo "Result has been copied to result.txt"
