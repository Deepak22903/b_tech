#!/bin/bash

string=$1

# Count the number of whitespace characters
whitespace_count=$(echo -n "$string" | grep -o '[[:space:]]' | wc -l)

echo "Number of whitespace characters: $whitespace_count"
