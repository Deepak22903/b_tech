#!/bin/bash

string=$1
old_word=$2
new_word=$3

# Replace the first occurrence
echo "Replacing the first occurrence:"
echo ${string/$old_word/$new_word}

# Replace all occurrences
echo "Replacing all occurrences:"
echo ${string//$old_word/$new_word}
