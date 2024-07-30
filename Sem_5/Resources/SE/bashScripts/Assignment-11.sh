# To read the contents of a file and display it line by line in command prompt. 

echo "Enter the name of the file: "
read fileName

if [ -f $fileName ]
then
    echo "File exists"
    while read line
    do
        echo $line
    done < $fileName
else
    echo "File does not exist"
fi

# Read All lines of the file
# echo "Enter the name of the file: "
# read fileName

# if [ -f $fileName ]
# then
#     echo "File exists"
#     cat $fileName
# else
#     echo "File does not exist"
# fi
