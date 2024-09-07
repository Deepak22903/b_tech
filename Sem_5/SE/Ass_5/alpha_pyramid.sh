#!/bin/bash

rows=5  # You can change this number for a different height
char=A  # Start with 'A'

for (( i=1; i<=rows; i++ ))
do
  for (( j=i; j<rows; j++ ))
  do
    echo -n " "  # Print spaces
  done
  for (( k=1; k<=i; k++ ))
  do
    echo -n "$char "  # Print characters
  done
  char=$(echo "$char" | tr "A-Y" "B-Z")  # Move to the next character
  echo  # New line
done
