# Bash Script To check the given number is odd or even. 

echo "Enter the number: "
read number

if [ `expr $number % 2` -eq 0 ]
then
    echo "The number is even"
else
    echo "The number is odd"
fi

