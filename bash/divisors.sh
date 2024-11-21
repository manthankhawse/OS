#!/bin/bash
# Script to print all divisors of a number

print_divisors() {
    local n=$1
    echo "Divisors of $n are:"
    for ((i = 1; i <= n; i++)); do
        if [ $((n % i)) -eq 0 ]; then
            echo "$i"
        fi
    done
}

read -p "Enter a number: " number
print_divisors $number
