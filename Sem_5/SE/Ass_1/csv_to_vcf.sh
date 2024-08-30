#!/bin/bash
if [ $# -ne 2 ]; then
echo "Usage: $0 input.csv output.vcf"
exit 1
fi
input_csv="$1"
output_vcf="$2"
{
while IFS=, read -r name phone email; do
echo "BEGIN:VCARD"
echo "VERSION:3.0"
echo "FN:$name"
echo "TEL;TYPE=CELL:$phone"
echo "EMAIL;TYPE=INTERNET:$email"
echo "END:VCARD"
done < "$input_csv"
}> "$output_vcf"
