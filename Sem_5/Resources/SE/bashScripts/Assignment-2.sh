# Bash Script To check the given integer is prime or not. 

echo "Enter the number: "
read number

if [ $number -eq 1 ] 
then
    echo "1 is neither prime nor composite"
    exit
elif [ $number -eq 0 ]
then
    echo "0 is neither prime nor composite"
    exit
fi


if [ $number -lt 0 ]
then
    echo "Number cannot be negative"
    exit
fi

i=2
flag=0
while [ $i -le `expr $number / 2` ]
do
    if [ `expr $number % $i` -eq 0 ]
    then
        flag=1
    fi
    i=`expr $i + 1`
done

if [ $flag -eq 1 ]
then
    echo "The number is not prime"
else
    echo "The number is prime"
fi
