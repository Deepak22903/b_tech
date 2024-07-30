# Bash Script To check and display 10 leap years from year 2000. 

year=2000
i=0
while [ $i -lt 10 ]
do
    if [ `expr $year % 4` -eq 0 ]
    then
        echo $year
        i=`expr $i + 1`
    fi
    year=`expr $year + 1`
done    
