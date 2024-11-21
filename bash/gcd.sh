#!/bin/bash  

gcd() { 

    local a=$1 

    local b=$2 

    while [ $b -ne 0 ]; do 

        local temp=$b 

        b=$((a % b)) 

        a=$temp 

    done 

    echo "GCD is: $a" 

} 

  

read num1 

read num2 

gcd $num1 $num2 

