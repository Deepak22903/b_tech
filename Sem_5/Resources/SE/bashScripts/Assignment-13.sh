# Bash Script To check the given string is palindrome or not. 

echo "Enter the string: "
read string

if [ $string == $(echo $string | rev) ]
then
    echo "Palindrome"
else
    echo "Not a Palindrome"
fi