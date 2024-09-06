string="Hello, World!"
if [[ $string == *"World"* ]]; then
  echo "String contains 'World'"
else
  echo "String does not contain 'World'"
fi
