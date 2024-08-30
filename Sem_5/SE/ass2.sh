#!/bin/bash
# string="Hello, World!"
# echo ${#string}
#
#  2. Substring Extraction Shell Commands To extract a substring:
# string="Hello, World!"
# echo ${string:7:5}  # Extracts "World"
#
# 3. String Replacement Shell Commands To replace the first occurrence of a substring:
# string="Hello, World!"
# echo ${string/World/Bash}  # Replaces "World" with "Bash"
# # Shell Commands To replace all occurrences:
# string="Hello, World! Welcome to the World!"
# echo ${string//World/Bash}  # Replaces all occurrences of "World" with "Bash"
#
# 4. Convert to Uppercase To convert a string to uppercase:
# string="Hello, World!"
# echo $(echo "$string" | tr '[:lower:]' '[:upper:]')
#
# 5. Convert to Lowercase Shell Commands To convert a string to lowercase:
string="Hello, World!"
echo $(echo "$string" | tr '[:upper:]' '[:lower:]')
