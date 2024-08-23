string="Hello, World!"
echo ${string/World/Bash}  # Replaces "World" with "Bash"
# Shell Commands To replace all occurrences:
string="Hello, World! Welcome to the World!"
echo ${string//World/Bash}  # Replaces all occurrences of "World" with "Bash"
