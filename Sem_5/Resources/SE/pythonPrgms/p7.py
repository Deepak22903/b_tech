import os
import filecmp
import math

from rich.panel import Panel
from rich.console import Console

rc = Console()

# 7. Find the Largest of 3 Numbers
def find_largest(num1, num2, num3):
    return f"Number 1 = {num1}\nNumber 2 = {num2}\nNumber 3 = {num3}\nLargest = {max(num1, num2, num3)}"

# print("Assignment 7")
rc.print(Panel(find_largest(5,2,7)+"\n"+find_largest(5,8,7), title="[green]Assignment-7[/green]"))

while True:
    try:
        num1 = int(input("Enter Number 1: "))
        num2 = int(input("Enter Number 2: "))
        num3 = int(input("Enter Number 3: "))
        print(find_largest(num1, num2, num3))
    except ValueError:
        print("Please enter a valid number!")
        continue