import os
import filecmp
import math

from rich.panel import Panel
from rich.console import Console

rc = Console()

# 3. Check if a Number is Odd or Even
def is_odd_or_even(num):
    if num % 2 == 0:
        return f"Number = {num}\nEven"
    else:
        return f"Number = {num}\nOdd"
    
# print("Assignment 3")
rc.print(Panel(is_odd_or_even(10)+"\n"+is_odd_or_even(7), title="[green]Assignment-3[/green]"))

while True:
    num=int(input("Enter Number: "))
    print(is_odd_or_even(num))