#!/bin/bash

# Prompt the user for the CSV file path
read -p "Enter the path to the CSV file: " csv_file

# Check if the input CSV file exists
if [ ! -f "$csv_file" ]; then
    echo "404 File not found: '$csv_file'"
    exit 1
fi

file_name=$(basename -- "$csv_file")
file_name_no_ext="${file_name%.*}"

output_vcf="$file_name_no_ext.vcf"
awk -F, '{printf "BEGIN:VCARD\nVERSION:3.0\nName:%s\nMobile:%s\nEND:VCARD\n", $1, $2}' "$csv_file" > "$output_vcf"
echo "CSV to VCF conversion completed. Result saved in '$output_vcf'."
