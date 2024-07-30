# Bash Script To check two file contents are same. ( hint: use cmp or diff  command ) 

echo "Enter the name of the first file: "
read fileName1

echo "Enter the name of the second file: "
read fileName2

if [ -f $fileName1 ] && [ -f $fileName2 ]
then
    echo "Files exist"
    if cmp -s $fileName1 $fileName2
    then
        echo "Files are same"
    else
        echo "Files are not same"
    fi
else
    echo "Files do not exist"
fi