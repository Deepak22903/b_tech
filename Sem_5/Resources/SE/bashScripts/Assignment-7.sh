# Find the largest of 3 numbers.  

echo "Enter the first number: "
read number1
echo "Enter the second number: "
read number2
echo "Enter the third number: "
read number3

if [ $number1 -gt $number2 ]
then
    if [ $number1 -gt $number3 ]
    then
        echo "$number1 is the largest number"
    else
        echo "$number3 is the largest number"
    fi
else
    if [ $number2 -gt $number3 ]
    then
        echo "$number2 is the largest number"
    else
        echo "$number3 is the largest number"
    fi
fi
