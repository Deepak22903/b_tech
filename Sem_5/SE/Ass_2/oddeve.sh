#!/bin/bash

echo "Enter the minimum value:"
read min
echo "Enter the maximum value:"
read max

if ! [[ "$min" =~ ^-?[0-9]+$ ]] || ! [[ "$max" =~ ^-?[0-9]+$ ]]; then
    echo "Invalid input. Please enter integer values."
    exit 1
fi

echo "Even numbers between $min and $max:"
for ((i=min; i<=max; i++)); do
    if (( i % 2 == 0 )); then
        echo "$i"
    fi
done

echo "Odd numbers between $min and $max:"
for ((i=min; i<=max; i++)); do
    if (( i % 2 != 0 )); then
        echo "$i"
    fi
done

