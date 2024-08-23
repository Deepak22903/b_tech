string="Hello, World!"
echo $(echo "$string" | tr '[:lower:]' '[:upper:]')
