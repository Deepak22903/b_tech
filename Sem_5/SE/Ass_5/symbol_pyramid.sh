#!/bin/bash

rows=5  # You can change this number for a different height

symbols=("₹" "##" "---" "++++")  # Array of special symbols

for (( i=1; i<=rows; i++ ))
do
  for (( j=i; j<rows; j++ ))
  do
    echo -n " "  # Print spaces
  done
  for (( k=1; k<=i; k++ ))
  do
    echo -n "${symbols[$(( (i-1) % ${#symbols[@]} ))]} "  # Print special symbols in cycle
  done
  echo  # New line
done
