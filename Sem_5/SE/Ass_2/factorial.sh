#!/bin/bash

echo "Enter a number:"
read n

if ! [[ "$n" =~ ^[0-9]+$ ]]; then
    echo "Error: Input must be a non-negative integer."
    exit 1
fi

factorial=1

while [ $n -gt 1 ]; do
    factorial=$((factorial * n))
    n=$((n - 1))
done

echo "Factorial is $factorial"

