import os
import filecmp
import math

from rich.panel import Panel
from rich.console import Console

rc = Console()

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

while True:
    try:
        num = int(input("Enter a number: "))
        print(is_prime(num))
    except ValueError:
        print("Please enter a valid number!")
        continue

