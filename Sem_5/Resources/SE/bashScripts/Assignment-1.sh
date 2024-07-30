# Bash Scirpt To find profit or loss given the cost price and selling price. 

echo "Enter the cost price of the item: "
read costPrice
if [ $costPrice -lt 0 ]
then
    echo "Cost Price cannot be negative"
    exit
fi

echo "Enter the selling price of the item: "
read sellingPrice

if [ $sellingPrice -lt 0 ]
then
    echo "Selling Price cannot be negative"
    exit
fi

if [ $costPrice -gt $sellingPrice ]
then
    echo "Loss: " $((costPrice - sellingPrice))
elif [ $costPrice -lt $sellingPrice ]
then
    echo "Profit: " $((sellingPrice - costPrice))
else
    echo "No Profit No Loss"
fi