# Bash Script To check if a file exists if yes then write "hello world" in the file if no then create the file and then write "hello world" line. 

echo "Enter the name of the file: "
read fileName

if [ -f $fileName ]
then
    echo "File exists"
    echo "Hello World" >> $fileName
else
    echo "File does not exist"
    touch $fileName
    echo "Hello World" >> $fileName
fi