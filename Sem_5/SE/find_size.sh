#!/bin/bash
if [ $# -ne 1 ]; then
echo "Usage: $0 directory"
exit 1
fi
directory="$1"
find "$directory" -type f -ctime -20 -exec ls -lh {} + | sort -k 5 -hr | head -n 10
