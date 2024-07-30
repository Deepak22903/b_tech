# BAsh Script To take subject marks as input from user and display the result (i-division, ii-division, iii-division, fail) 

echo "Enter the marks of the first subject: "
read subject1

if [ $subject1 -lt 0 ] || [ $subject1 -gt 100 ]
then
    echo "Invalid Input"
    exit
fi

echo "Enter the marks of the second subject: "
read subject2

if [ $subject2 -lt 0 ] || [ $subject2 -gt 100 ]
then
    echo "Invalid Input"
    exit
fi

echo "Enter the marks of the third subject: "
read subject3

if [ $subject3 -lt 0 ] || [ $subject3 -gt 100 ]
then
    echo "Invalid Input"
    exit
fi

echo "Enter the marks of the fourth subject: "
read subject4

if [ $subject4 -lt 0 ] || [ $subject4 -gt 100 ]
then
    echo "Invalid Input"
    exit
fi

echo "Enter the marks of the fifth subject: "
read subject5

if [ $subject5 -lt 0 ] || [ $subject5 -gt 100 ]
then
    echo "Invalid Input"
    exit
fi

percentage=`echo \($subject1 + $subject2 + $subject3 + $subject4 + $subject5\) / 5 | bc`

if [ $percentage -gt 100 ] || [ $percentage -lt 0 ]
then
    echo "Invalid Input"
elif [ $percentage -ge 80 ]
then
    echo "First Division"
elif [ $percentage -ge 60 ]
then
    echo "Second Division"
elif [ $percentage -ge 40 ]
then
    echo "Third Division"
else
    echo "Fail"
fi
