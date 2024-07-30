# Simple calculator for basic arithmetic operations. (take operand-1, operator and operand-2 from user as input)

echo "Enter the first number: "
read operand1
echo "Enter the second number: "
read operand2

echo "Enter the operator: "
read operator

case $operator in
    +) echo "Sum: " `expr $operand1 + $operand2`;;
    -) echo "Difference: " `expr $operand1 - $operand2`;;
    \*) echo "Product: " `expr $operand1 \* $operand2`;;
    /) echo "Quotient: " `expr $operand1 / $operand2`;;
    %) echo "Remainder: " `expr $operand1 % $operand2`;;
    *) echo "Invalid operator"
esac
