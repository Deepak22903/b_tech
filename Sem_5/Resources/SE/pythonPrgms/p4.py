import os
import filecmp
import math

from rich.panel import Panel
from rich.console import Console

rc = Console()

# 4. Calculate Area and Circumference of a Circle
def calculate_circle_properties(radius):
    area = math.pi * radius ** 2
    circumference = 2 * math.pi * radius
    return f"Radius = {radius}\nArea = {area}\nCircumference = {circumference}"

# print("Assignment 4")
rc.print(Panel(calculate_circle_properties(10), title="[green]Assignment-4[/green]"))

while True:
    try:
        radius = float(input("Enter Radius: "))
        print(calculate_circle_properties(radius))
    except ValueError:
        print("Please enter a valid number!")
        continue