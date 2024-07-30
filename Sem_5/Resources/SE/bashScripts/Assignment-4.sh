# Bash Script To find the area and circumference of a circle. 

echo "Enter the radius of the circle: "
read radius

if [ $radius -lt 0 ]
then
    echo "Radius cannot be negative"
    exit
fi

area=`echo 3.14 \* $radius \* $radius | bc`
circumference=`echo 2 \* 3.14 \* $radius | bc`

echo "Area of the circle: " $area
echo "Circumference of the circle: " $circumference
