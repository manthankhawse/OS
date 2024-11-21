#!/bin/bash

read age
if [ "$age" -ge 18 ]; then
    echo "You are eligible to apply for a driving license."
else
    echo "You are not eligible to apply for a driving license."
fi
