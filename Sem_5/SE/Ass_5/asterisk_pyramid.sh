#!/bin/bash

rows=5  # You can change this number for a different height

for (( i=1; i<=rows; i++ ))
do
  for (( j=i; j<rows; j++ ))
  do
    echo -n " "  # Print spaces
  done
  for (( k=1; k<=2*i-1; k++ ))
  do
    echo -n "*"  # Print asterisks
  done
  echo  # New line
done
