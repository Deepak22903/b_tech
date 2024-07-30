import os
import filecmp
import math

from rich.panel import Panel
from rich.console import Console

rc = Console()

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

while True:
    try:
        mark = list(map(int, input("Enter marks: ").split()))
        print(calculate_subject_result(mark))
    except ValueError:
        print("Please enter a valid number!")
        continue
