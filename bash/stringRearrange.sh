#!/bin/bash

# Function to count characters in a string and store in an associative array
count_chars() {
    declare -A char_count
    str="$1"

    for (( i=0; i<${#str}; i++ )); do
        char="${str:$i:1}"
        ((char_count[$char]++))
    done

    # Print the associative array in a sorted manner (to compare with other string)
    for key in "${!char_count[@]}"; do
        echo "$key ${char_count[$key]}"
    done | sort
}

# Check if two strings were passed as arguments
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <string1> <string2>"
    exit 1
fi

string1=$1
string2=$2

# If the lengths of the strings are different, they can't be rearranged
if [ ${#string1} -ne ${#string2} ]; then
    echo "String 1 cannot be rearranged to form String 2."
    exit 0
fi

# Compare character counts of both strings
if [ "$(count_chars "$string1")" == "$(count_chars "$string2")" ]; then
    echo "String 1 can be rearranged to form String 2."
else
    echo "String 1 cannot be rearranged to form String 2."
fi

