#!/bin/bash

echo "Enter the number of terms for the Fibonacci series:"
read n

if ! [[ "$n" =~ ^[0-9]+$ ]] || [ "$n" -le 0 ]; then
    echo "Error: Please enter a positive integer."
    exit 1
fi

a=0
b=1

echo "Fibonacci series up to $n terms:"

for ((i=0; i<n; i++)); do
    echo -n "$a "
    fib=$((a + b))
    a=$b
    b=$fib
done

echo

