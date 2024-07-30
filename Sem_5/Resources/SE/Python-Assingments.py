import os
import filecmp
import math

from rich.panel import Panel
from rich.console import Console

rc = Console()

# 1. Find Profit or Loss
def calculate_profit_or_loss(cost_price, selling_price):
    if cost_price < selling_price:
        return f"Cost Price = {cost_price} \nSelling Price = {selling_price}\nProfit"
    elif cost_price > selling_price:
        return f"Cost Price = {cost_price} \nSelling Price = {selling_price}\nLoss"
    else:
        return f"Cost Price = {cost_price} \nSelling Price = {selling_price}\nNo Profit No Loss"
       
# print("Assignment 1")
rc.print(Panel(calculate_profit_or_loss(500, 50), title="[green]Assignment-1[/green]"))


# 2. Check if a Number is Prime
def is_prime(num):
    if num <= 1:
        return False
    for i in range(2, int(num**0.5) + 1):
        if num % i == 0:
            return f"Number = {num}\nNot Prime!"
    return f"Number = {num}\nPrime!"

# print("Assignment 2")
rc.print(Panel(is_prime(10)+"\n"+is_prime(7), title="[green]Assignment-2[/green]"))


# 3. Check if a Number is Odd or Even
def is_odd_or_even(num):
    if num % 2 == 0:
        return f"Number = {num}\nEven"
    else:
        return f"Number = {num}\nOdd"
    
# print("Assignment 3")
rc.print(Panel(is_odd_or_even(10)+"\n"+is_odd_or_even(7), title="[green]Assignment-3[/green]"))


# 4. Calculate Area and Circumference of a Circle
def calculate_circle_properties(radius):
    area = math.pi * radius ** 2
    circumference = 2 * math.pi * radius
    return f"Radius = {radius}\nArea = {area}\nCircumference = {circumference}"

# print("Assignment 4")
rc.print(Panel(calculate_circle_properties(10), title="[green]Assignment-4[/green]"))


# 5. Calculate Subject Result
def calculate_subject_result(mark):

    marks = sum(mark) / len(mark)
    if marks >= 90:
        return f"Total Marks = {marks}\nI-Division"
    elif 80 <= marks < 90:
        return f"Total Marks = {marks}\nII-Division"
    elif 70 <= marks < 80:
        return f"Total Marks = {marks}\nIII-Division"
    else:
        return f"Total Marks = {marks}\nFail"
    
# print("Assignment 5")
rc.print(Panel(calculate_subject_result([95, 85, 86, 92, 91]), title="[green]Assignment-5[/green]"))


# 6. Simple Calculator
def calculator(operand1, operator, operand2):
    if operator == '+':
        return f"{operand1} {operator} {operand2} = {operand1 + operand2}"
    elif operator == '-':
        return f"{operand1} {operator} {operand2} = {operand1 - operand2}"
    elif operator == '*':
        return f"{operand1} {operator} {operand2} = {operand1 * operand2}"
    elif operator == '/':
        if operand2 == 0:
            return f"{operand1} {operator} {operand2} = {operand1 / operand2}\nCannot divide by zero"
        return f"{operand1} {operator} {operand2} = {operand1 / operand2}"
    else:
        return f"Invalid Operator"
    
# print("Assignment 6")
rc.print(Panel(calculator(50,  '+', 60)+"\n"+calculator(50,  '-', 60)+"\n"+calculator(50,  '*', 60)+"\n"+calculator(500, '/', 60), title="[green]Assignment-6[/green]"))


# 7. Find the Largest of 3 Numbers
def find_largest(num1, num2, num3):
    return f"Number 1 = {num1}\nNumber 2 = {num2}\nNumber 3 = {num3}\nLargest = {max(num1, num2, num3)}"

# print("Assignment 7")
rc.print(Panel(find_largest(5,2,7)+"\n"+find_largest(5,8,7), title="[green]Assignment-7[/green]"))


# 8. Display Student Result
def display_student_result(marks):
    # Using match-case
    result = sum(marks) / len(marks)
    match result:
        case result if result >= 90:
            result = "I-Division"
        case result if 80 <= result < 90:
            result = "II-Division"
        case result if 70 <= result < 80:
            result = "III-Division"
        case _:
            result = "Fail" 

    return f"Total Marks = {sum(marks)}\nResult = {result}"

rc.print(Panel(display_student_result([95, 85, 86, 92, 91]), title="[green]Assignment-8[/green]"))


# 9. Check and Write to a File
def check_and_write_to_file(filename):
    if os.path.exists(filename):
        with open(filename, 'a') as file:
            file.write("hello world\n")
    else:
        with open(filename, 'w') as file:
            file.write("hello world\n")

def display_file_contents(filename):
    string=""
    if os.path.exists(filename):
        with open(filename, 'r') as file:
            for line in file:
                string += line
    else:
        return f"File '{filename}' does not exist."
    return string

# print("Assignment 9")
check_and_write_to_file('test_file.txt')
rc.print(Panel(display_file_contents('test_file.txt'), title="[green]Assignment-9[/green]"))


# 10. Create a Directory
def create_directory(directory_name):
    if not os.path.exists(directory_name):
        os.mkdir(directory_name)
        return f"Directory '{directory_name}' created successfully."
    else:
        return f"Directory '{directory_name}' already exists."

# print("Assignment 10")
rc.print(Panel(create_directory('test_dir'), title="[green]Assignment-10[/green]"))


# 11. Read and Display File Contents Line by Line
def read_and_display_file(filename):
    string=""
    if os.path.exists(filename):
        with open(filename, 'r') as file:
            for line in file:
                string += line
    else:
        return f"File '{filename}' does not exist."
    return string

# print("Assignment 11")
rc.print(Panel(read_and_display_file('test_file.txt'), title="[green]Assignment-11[/green]"))


# 12. Check Leap Years
def find_leap_years(start_year, num_years):
    leap_years = []
    while num_years:
        if (start_year % 4 == 0 and start_year % 100 != 0) or (start_year % 400 == 0):
            leap_years.append(start_year)
            num_years -= 1 
        start_year += 1

    return f"Leap Years = {leap_years}"

# print("Assignment 12")
rc.print(Panel(find_leap_years(2000, 10), title="[green]Assignment-12[/green]"))


# 13. Check if a String is Palindrome
def is_palindrome(string):
    string = string.lower().replace(" ", "")
    if string == string[::-1]:
        return f"String = {string}\nPalindrome"
    else:
        return f"String = {string}\nNot Palindrome"
    
# print("Assignment 13")
rc.print(Panel(is_palindrome('aba')+"\n"+is_palindrome('abasd'), title="[green]Assignment-13[/green]"))


# 14. Find the Factorial of a Number
def factorial(num):
    if num == 1:
        return 1
    else:
        return num * factorial(num - 1)
    
# print("Assignment 14")
rc.print(Panel(str(factorial(4))+"\n"+str(factorial(5)), title="[green]Assignment-14[/green]"))


# 15. Check if Two Files Have the Same Contents
def are_files_equal(file1, file2):
    return f"Files are equal: {filecmp.cmp(file1, file2)}"

# print("Assignment 15")
rc.print(Panel(are_files_equal('cmp1.txt', 'cmp2.txt'), title="[green]Assignment-15[/green]"))


# 16. Print Pyramid
def print_pyramid(rows):
    string = ""
    for i in range(1, rows + 1):
        for j in range(1, rows - i + 1):
            string += " "
        for k in range(1, i * 2):
            string += "*"
        string += "\n"
    return string

# print("Assignment 16")
rc.print(Panel(print_pyramid(5)+"\n"+print_pyramid(8), title="[green]Assignment-16[/green]"))


def print_pyramid_nums(height):   
    string = ""                                                 
    for i in range(1, height + 1):                                             
        for j in range(1, height - i + 1):                                     
            string += " "
        for k in range(1, i + 1):                                              
            string += str(k)                                              
        for l in range(i - 1, 0, -1):                                          
            string += str(l)                                                   
        string += "\n"
    return string

# print("Assignment 16 with numbers")
rc.print(Panel(print_pyramid_nums(5)+"\n"+print_pyramid_nums(8), title="[green]Assignment-16[/green]"))


# 17. Modify and Display a File Using grep
def modify_and_display_file(filename):
    f = open("filename", 'w')
    # Random Names Of Cities
    s= """
    Mumbai
    Delhi
    Bangalore
    Hyderabad
    Ahmedabad
    Chennai
    Kolkata
    """.split()

    s = [line for line in s if "a" not in line]
    f.writelines('\n'.join(s))
    f.close()

    f = open("filename", 'r')
    string = ""
    for line in f:
        string += line
    f.close()
    return string

# print("Assignment 17")
rc.print(Panel(modify_and_display_file('test_file.txt'), title="[green]Assignment-17[/green]"))


