#!/bin/bash

if [ "$#" -ne 3 ]; then
    echo "Usage: $0 <num1> <operator> <num2>"
    exit 1
fi

num1=$1
operator=$2
num2=$3

case "$operator" in
    "+")
        result=$((num1 + num2))
        ;;
    "-")
        result=$((num1 - num2))
        ;;
    "*")
        result=$((num1 * num2))
        ;;
    "/")
        if [ "$num2" -eq 0 ]; then
            echo "Error: Division by zero"
            exit 1
        else
            result=$((num1 / num2))
        fi
        ;;
    *)
        echo "Invalid operator. Use +, -, *, or /."
        exit 1
        ;;
esac

echo "Result: $result"

