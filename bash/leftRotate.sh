#!/bin/bash
# Script to display left rotated sequence of an array

left_rotate() {
    local arr=("$@")
    local n=${#arr[@]}
    local shift=1  # Number of positions to shift
    echo "Original array: ${arr[@]}"
    for ((i = 0; i < n; i++)); do
        echo -n "${arr[(($i + $shift) % $n)]} "
    done
    echo
}

read -p "Enter array elements separated by space: " -a array
left_rotate "${array[@]}"
