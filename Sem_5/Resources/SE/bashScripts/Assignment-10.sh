# Bash Script to Make a directory after checking of its existence

echo "Enter the name of the directory: "
read directoryName

if [ -d $directoryName ]
then
    echo "Directory already exists"
else
    mkdir $directoryName
    echo "Directory created successfully"
fi
