#!/bin/bash
if [ $# -ne 2 ]; then
echo "Usage: $0 input.txt output.srt"
exit 1
fi
input_txt="$1"
output_srt="$2"
{
counter=1
while IFS= read -r line; do
echo "$counter"
echo "$line"
echo ""
counter=$((counter + 1))
done < "$input_txt"
} > "$output_srt"
