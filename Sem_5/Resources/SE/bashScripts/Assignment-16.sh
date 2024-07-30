# Bash Script To print a pyramid of numbers in different formats (numeric, special character)

echo "Enter the number of rows: "
read rows

echo "Enter the character: "
read character

echo "==============";

# Left Aligned
for (( i=1; i<=rows; i++ ))
do
    for (( j=1; j<=i; j++ ))
    do
        echo -n "$character "
    done
    echo
done

echo "==============";

# Center Aligned
for (( i=1; i<=rows; i++ ))
do
    for (( j=rows; j>=i; j-- ))
    do
        echo -n " "
    done
    for (( j=1; j<=i; j++ ))
    do
        echo -n "$character "
    done
    echo
done

# Generate numbers in increasing order and put in center aligned pyramid
echo "==============";

for (( i=1; i<=rows; i++ ))
do
    n1=0
    for (( j=rows; j>=i; j-- ))
    do
        echo -n " "
    done
    for (( j=1; j<=i; j++ ))
    do
        n1=$((n1+1))
        echo -n "$n1 "
    done
    echo
done
