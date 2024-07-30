import os
import filecmp
import math

from rich.panel import Panel
from rich.console import Console

rc = Console()

# 14. Find the Factorial of a Number
def factorial(num):
    if num == 1:
        return 1
    else:
        return num * factorial(num - 1)
    
# print("Assignment 14")
rc.print(Panel(str(factorial(4))+"\n"+str(factorial(5)), title="[green]Assignment-14[/green]"))


while True:
    try:
        num = int(input("Enter a number: "))
        print(factorial(num))
    except ValueError:
        print("Please enter a valid number!")
        continue