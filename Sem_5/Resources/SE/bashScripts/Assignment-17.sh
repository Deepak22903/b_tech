# To write the following contents in a file:- 

# Create a file
touch file.txt

# Write contents to file
echo "Cat
dog
bear
hello
elephant
hello
tiger
hello
horse" > file.txt

cat file.txt
echo "==============";
# Delete lines containing "hello"

grep -v "hello" file.txt > file2.txt

# Display the file
cat file2.txt
echo "==============";

# Delete the file
rm file.txt file2.txt

