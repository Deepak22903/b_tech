#!/bin/bash

find . -type f -mtime -20 -exec ls -lh {} \; | sort -k5 -hr | head -n 10
echo "----------"
find /home -type f -mtime -20 -exec ls -lh {} \; | sort -k5 -hr | head -n 10
