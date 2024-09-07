#!/bin/bash

rows=5  # You can change this number for a different height

for (( i=1; i<=rows; i++ ))
do
  for (( j=i; j<rows; j++ ))
  do
    echo -n " "  # Print spaces
  done
  for (( k=1; k<=i; k++ ))
  do
    echo -n "$i "  # Print numbers
  done
  echo  # New line
done
