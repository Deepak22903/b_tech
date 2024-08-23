string="Hello, World!"
echo $(echo "$string" | tr '[:upper:]' '[:lower:]')
