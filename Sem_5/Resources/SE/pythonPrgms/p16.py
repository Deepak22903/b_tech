import os
import filecmp
import math

from rich.panel import Panel
from rich.console import Console

rc = Console()

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

while True:
    try:
        rows = int(input("Enter number of rows: "))
        print(print_pyramid(rows))
    except ValueError:
        print("Please enter a valid number!")
        continue

    try:
        rows = int(input("Enter number of rows: "))
        print(print_pyramid_nums(rows))
    except ValueError:
        print("Please enter a valid number!")
        continue