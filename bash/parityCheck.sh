#!/bin/bash

check_parity() {
    # First argument is the array size
    local size=$1
    shift
    # Remaining arguments are the array elements
    local first_parity=$(( $1 % 2 ))
    
    for ((i = 1; i < size; i++)); do
        if [ $(( $i % 2 )) -ne $first_parity ]; then
            echo "Not all elements have equal parity."
            return
        fi
    done
    
    echo "All elements have equal parity."
}

# Read array size and elements
echo "Enter array size followed by elements separated by spaces:"
read -a input

# First value is the size of the array
size=${input[0]}
# Remaining values are the array elements
array_elements="${input[@]:1}"

# Call function with array size and elements
check_parity $size ${array_elements[@]}
