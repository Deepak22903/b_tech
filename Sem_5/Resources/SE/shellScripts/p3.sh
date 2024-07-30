#!/bin/bash
# Destination directory where duplicates will be moved
dest_dir="./duplicates"

# Create the destination directory if it doesn't exist
mkdir -p "$dest_dir"

# Associative array to store file checksums
declare -A checksums

# Find all files in the current directory and its subdirectories
find . -type f -print0 | while IFS= read -r -d '' file; do
  # Calculate the MD5 checksum for the file
  checksum=$(md5sum "$file" | awk '{print $1}')
  
  # Check if a file with the same checksum already exists in the destination directory
  if [[ -n ${checksums[$checksum]} ]]; then
    # Move the file to the destination directory
    mv "$file" "$dest_dir"
    echo "Moved: $file"
  else
    # Store the checksum of the file
    checksums[$checksum]="$file"
  fi
done

echo "Duplicate files moved to: $dest_dir"
