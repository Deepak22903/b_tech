# Bash script To find the factorial of a number. 

echo "Enter the number: "
read number

if [ $number -lt 0 ]
then
    echo "Number cannot be negative"
    exit
fi

factorial=1

for (( i=1; i<=number; i++ ))
do
    factorial=$((factorial*i))
done

echo "Factorial of $number is $factorial"

# -ve num